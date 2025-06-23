#include "optimizer.h"

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <memory>
#include <utility>

#include "query/executor/expr/exprs.h"
#include "query/executor/query_iter.h"
#include "query/executor/query_iters.h"
#include "query/parser/logical_plan/expr/expr_plans.h"
#include "query/parser/logical_plan/plans.h"
#include "relational_model/schema.h"
#include "system/system.h"

std::unique_ptr<QueryIter> Optimizer::create_physical_plan(std::unique_ptr<LogicalPlan> logical_plan) {
  Optimizer optimizer;
  logical_plan->accept_visitor(optimizer);
  return std::move(optimizer.current_iter);
}

void Optimizer::visit(CartesianProductPlan& cartesian_product) {
  assert(cartesian_product.children.size() >= 2);

  cartesian_product.children[0]->accept_visitor(*this);
  for (size_t i = 1; i < cartesian_product.children.size(); i++) {
    std::vector<ProjectedColumn> projected_lhs_columns;
    std::vector<ProjectedColumn> projected_rhs_columns;
    std::vector<std::pair<size_t, size_t>> equalities;

    auto lhs = std::move(current_iter);
    cartesian_product.children[i]->accept_visitor(*this);
    auto rhs = std::move(current_iter);

    auto lhs_columns = lhs->get_columns();
    auto rhs_columns = rhs->get_columns();
    for (size_t i = 0; i < lhs_columns.size(); i++) {
      if (column_usage[lhs_columns[i]] > 0) {
        projected_lhs_columns.emplace_back(i, lhs_columns[i]);
      }
    }
    for (size_t i = 0; i < rhs_columns.size(); i++) {
      if (column_usage[rhs_columns[i]] > 0) {
        projected_rhs_columns.emplace_back(i, rhs_columns[i]);
      }
    }

    current_iter = std::make_unique<CartesianProduct>(
        std::move(lhs), std::move(rhs), std::move(projected_lhs_columns), std::move(projected_rhs_columns)
    );
  }
}

void Optimizer::visit(ProjectionPlan& projection) {
  if (projection.distinct) {
    throw NotImplementedException("Projection with DISTINCT");
  }
  for (const auto& column : projection.columns) {
    column_usage[column] += 1;
  }
  projection.child->accept_visitor(*this);
  current_iter =
      std::make_unique<Projection>(std::move(current_iter), std::move(projection.columns), projection.limit);
}

void Optimizer::visit(SelectionPlan& selection) {
  auto* child_relation = dynamic_cast<RelationPlan*>(selection.child.get());
  bool child_is_relation = child_relation != nullptr;

  for (const auto& e : selection.expressions) {
    for (auto& column : e->get_columns()) {
      column_usage[column] += 1;
    }
    if (child_is_relation) {
      auto* between_plan_expr = dynamic_cast<ExprPlanBetween*>(e.get());
      if (between_plan_expr != nullptr) {
        auto* index = catalog.get_index(child_relation->table);
        if (index != nullptr) {
          auto index_column =
              catalog.get_table_info(child_relation->table).schema->columns[index->get_key_column_idx()];
          if (between_plan_expr->child->column.info == index_column) {
            try_set_lower_bound(between_plan_expr->child->column, std::move(between_plan_expr->lower_bound));
            try_set_upper_bound(between_plan_expr->child->column, std::move(between_plan_expr->upper_bound));
            between_optimizations.insert(
                {between_plan_expr->child->column.alias, between_plan_expr->child->column}
            );
            deleted_expr_plans.insert(e.get());
          }
        }
      }
    }
  }

  selection.child->accept_visitor(*this);

  std::vector<std::unique_ptr<Expr>> expressions;
  for (auto& e : selection.expressions) {
    for (auto& column : e->get_columns()) {
      column_usage[column] -= 1;
    }
    if (deleted_expr_plans.find(e.get()) == deleted_expr_plans.end()) {
      ExprOptimizer expr_visitor(current_iter->get_columns(), current_iter->get_output());
      e->accept_visitor(expr_visitor);
      expressions.push_back(std::move(expr_visitor.current_expr));
    }
  }

  if (expressions.size() > 0) {
    current_iter = std::make_unique<Selection>(std::move(current_iter), std::move(expressions));
  }
}

void Optimizer::visit(RelationPlan& relation) {
  Schema schema;
  auto table = catalog.get_table(relation.table, &schema);
  assert(table != nullptr);

  std::vector<ProjectedColumn> project_columns;

  for (size_t i = 0; i < schema.columns.size(); i++) {
    Column column(relation.alias, relation.table, ColumnInfo(schema.columns[i]));
    if (column_usage[column] > 0) {
      project_columns.emplace_back(i, column);
    }
  }

  std::unique_ptr<RelationIter> relation_iter;
  auto opt = between_optimizations.find(relation.alias);
  if (opt != between_optimizations.end()) {
    auto opt_range = column_range.find(opt->second);
    auto* index = catalog.get_index(relation.table);
    assert(schema.columns[index->get_key_column_idx()] == opt->second.info);
    relation_iter = index->get_iter(opt_range->second.first, opt_range->second.second);
  } else {
    relation_iter = table->get_record_iter();
  }

  current_iter = std::make_unique<Relation>(std::move(relation_iter), schema, std::move(project_columns));
}

void Optimizer::visit(JoinPlan& join) {
  for (const auto& join_column : join.join_columns) {
    column_usage[join_column.first] += 1;
    column_usage[join_column.second] += 1;
  }

  join.children[0]->accept_visitor(*this);

  for (size_t j_i = 1; j_i < join.children.size(); j_i++) {
    std::vector<ProjectedColumn> projected_lhs_columns;
    std::vector<ProjectedColumn> projected_rhs_columns;
    std::vector<std::pair<size_t, size_t>> equalities;

    auto lhs = std::move(current_iter);
    join.children[j_i]->accept_visitor(*this);
    auto rhs = std::move(current_iter);

    auto lhs_columns = lhs->get_columns();
    auto rhs_columns = rhs->get_columns();
    for (size_t i = 0; i < lhs_columns.size(); i++) {
      if (column_usage[lhs_columns[i]] > 0) {
        projected_lhs_columns.emplace_back(i, lhs_columns[i]);
      }
    }
    for (size_t i = 0; i < rhs_columns.size(); i++) {
      if (column_usage[rhs_columns[i]] > 0) {
        projected_rhs_columns.emplace_back(i, rhs_columns[i]);
      }
    }

    for (const auto& column_pair : join.join_columns) {
      if (lhs_columns.size() == 0 || rhs_columns.size() == 0) {
        break;
      }

      bool swap = column_pair.first.alias == rhs_columns[0].alias;
      auto lhs_column = swap ? column_pair.second : column_pair.first;
      auto rhs_column = swap ? column_pair.first : column_pair.second;

      int lhs_column_pos = -1;
      int rhs_column_pos = -1;
      for (size_t i = 0; i < lhs_columns.size(); i++) {
        if (lhs_columns[i] == lhs_column) {
          lhs_column_pos = i;
          break;
        }
      }
      for (size_t i = 0; i < rhs_columns.size(); i++) {
        if (rhs_columns[i] == rhs_column) {
          rhs_column_pos = i;
          break;
        }
      }
      if (lhs_column_pos != -1 && rhs_column_pos != -1) {
        equalities.emplace_back(lhs_column_pos, rhs_column_pos);
      }
    }

    if (equalities.empty()) {
      current_iter = std::make_unique<CartesianProduct>(
          std::move(lhs), std::move(rhs), std::move(projected_lhs_columns), std::move(projected_rhs_columns)
      );
    } else {
      current_iter = std::make_unique<Join>(
          std::move(lhs), std::move(rhs), std::move(projected_lhs_columns), std::move(projected_rhs_columns),
          std::move(equalities)
      );
    }
  }

  for (const auto& join_column : join.join_columns) {
    column_usage[join_column.first] -= 1;
    column_usage[join_column.second] -= 1;
  }
}

void Optimizer::visit(LeftOuterJoinPlan& join) {
  for (const auto& join_column : join.columns) {
    column_usage[join_column.first] += 1;
    column_usage[join_column.second] += 1;
  }

  join.lchild->accept_visitor(*this);
  auto lhs = std::move(current_iter);
  join.rchild->accept_visitor(*this);
  auto rhs = std::move(current_iter);

  auto lhs_columns = lhs->get_columns();
  auto rhs_columns = rhs->get_columns();
  std::vector<ProjectedColumn> projected_lhs_columns, projected_rhs_columns;

  for (size_t i = 0; i < lhs_columns.size(); i++) {
    if (column_usage[lhs_columns[i]] > 0) {
      projected_lhs_columns.emplace_back(i, lhs_columns[i]);
    }
  }
  for (size_t i = 0; i < rhs_columns.size(); i++) {
    if (column_usage[rhs_columns[i]] > 0) {
      projected_rhs_columns.emplace_back(i, rhs_columns[i]);
    }
  }

  std::vector<std::pair<size_t, size_t>> equalities;
  for (const auto& column_pair : join.columns) {
    if (lhs_columns.size() == 0 || rhs_columns.size() == 0) {
      break;
    }

    bool swap = column_pair.first.table == rhs_columns[0].table;
    auto lhs_col = swap ? column_pair.second : column_pair.first;
    auto rhs_col = swap ? column_pair.first : column_pair.second;

    int lhs_col_pos = -1;
    int rhs_col_pos = -1;

    for (size_t i = 0; i < lhs_columns.size(); i++) {
      if (lhs_columns[i].info == lhs_col.info) {
        lhs_col_pos = i;
        break;
      }
    }
    for (size_t i = 0; i < rhs_columns.size(); i++) {
      if (rhs_columns[i].info == rhs_col.info) {
        rhs_col_pos = i;
        break;
      }
    }
    if (lhs_col_pos != -1 && rhs_col_pos != -1) {
      equalities.push_back({lhs_col_pos, rhs_col_pos});
    }
  }

  current_iter = std::make_unique<LeftOuterJoin>(
      std::move(lhs), std::move(rhs), std::move(projected_lhs_columns), std::move(projected_rhs_columns),
      std::move(equalities)
  );

  for (const auto& join_column : join.columns) {
    column_usage[join_column.first] -= 1;
    column_usage[join_column.second] -= 1;
  }
}

void ExprOptimizer::visit(ExprPlanColumn& e) {
  int index = -1;
  for (size_t i = 0; i < columns.size(); i++) {
    if (e.column == columns[i]) {
      index = i;
      break;
    }
  }
  assert(index != -1);
  current_expr = std::make_unique<ExprColumn>(e.column, output.values[index]);
}

void ExprOptimizer::visit(ExprPlanTerm& e) {
  current_expr = std::make_unique<ExprTerm>(std::move(e.value));
}

void ExprOptimizer::visit(ExprPlanEquals& e) {
  e.lhs->accept_visitor(*this);
  auto lhs = std::move(current_expr);
  e.rhs->accept_visitor(*this);
  auto rhs = std::move(current_expr);
  current_expr = std::make_unique<ExprEquals>(std::move(lhs), std::move(rhs));
}

void ExprOptimizer::visit(ExprPlanNotEquals& e) {
  e.lhs->accept_visitor(*this);
  auto lhs = std::move(current_expr);
  e.rhs->accept_visitor(*this);
  auto rhs = std::move(current_expr);
  current_expr = std::make_unique<ExprNotEquals>(std::move(lhs), std::move(rhs));
}

void ExprOptimizer::visit(ExprPlanLess& e) {
  e.lhs->accept_visitor(*this);
  auto lhs = std::move(current_expr);
  e.rhs->accept_visitor(*this);
  auto rhs = std::move(current_expr);
  current_expr = std::make_unique<ExprLess>(std::move(lhs), std::move(rhs));
}

void ExprOptimizer::visit(ExprPlanLessOrEquals& e) {
  e.lhs->accept_visitor(*this);
  auto lhs = std::move(current_expr);
  e.rhs->accept_visitor(*this);
  auto rhs = std::move(current_expr);
  current_expr = std::make_unique<ExprLessOrEquals>(std::move(lhs), std::move(rhs));
}

void ExprOptimizer::visit(ExprPlanBetween& e) {
  e.child->accept_visitor(*this);
  current_expr = std::make_unique<ExprBetween>(
      std::move(current_expr), std::move(e.lower_bound), std::move(e.upper_bound)
  );
}

void ExprOptimizer::visit(ExprPlanLike& e) {
  e.column->accept_visitor(*this);
  current_expr = std::make_unique<ExprLike>(std::move(current_expr), std::move(e.pattern));
}

void Optimizer::try_set_lower_bound(const Column& column, Value&& value) {
  auto opt_range = column_range.find(column);

  Value max = value;
  if (value.datatype == DataType::INT) {
    max.value.as_int = INT64_MAX;
  } else {
    max.value.as_str[0] = std::numeric_limits<unsigned char>::max();
  }

  if (opt_range == column_range.end()) {
    column_range.insert({column, {std::move(value), max}});
    return;
  }

  // If new lower bound is greater than previous one, update.
  if (opt_range->second.first < value) {
    opt_range->second.first = std::move(value);
  }
}

void Optimizer::try_set_upper_bound(const Column& column, Value&& value) {
  auto opt_range = column_range.find(column);

  Value min = value;
  if (value.datatype == DataType::INT) {
    min.value.as_int = INT64_MIN;
  } else {
    min.value.as_str[0] = std::numeric_limits<unsigned char>::min();
  }

  if (opt_range == column_range.end()) {
    column_range.insert({column, {std::move(value), min}});
    return;
  }

  // If new upper bound is lower than previous one, update.
  if (opt_range->second.first > value) {
    opt_range->second.first = std::move(value);
  }
}

#pragma once

#include <map>
#include <memory>

#include "query/parser/logical_plan/plans.h"

namespace Parser::QueryRewriter {

// This visitor pushes Selection's simple expressions down
class PushSelection : public LogicalPlanVisitor {
public:
  void visit(CartesianProductPlan& cartesian_product) override {
    std::vector<std::unique_ptr<LogicalPlan>> new_children;

    for (auto& child : cartesian_product.children) {
      child->accept_visitor(*this);
      new_children.push_back(std::move(current_plan));
    }
    current_plan = std::make_unique<CartesianProductPlan>(std::move(new_children));
  }

  void visit(ProjectionPlan& projection) override {
    projection.child->accept_visitor(*this);

    current_plan = std::make_unique<ProjectionPlan>(
        std::move(current_plan), projection.distinct, projection.limit, std::move(projection.columns)
    );
  }

  void visit(SelectionPlan& selection) override {
    std::vector<std::unique_ptr<ExprPlan>> remaining_expressions;

    for (auto& expression : selection.expressions) {
      const auto columns = expression->get_columns();
      if (columns.size() == 1) {
        // Simple expression
        id2simple_expressions[std::pair(columns.begin()->alias, columns.begin()->table)].push_back(
            std::move(expression)
        );
      } else {
        remaining_expressions.push_back(std::move(expression));
      }
    }

    selection.child->accept_visitor(*this);

    if (!remaining_expressions.empty()) {
      current_plan =
          std::make_unique<SelectionPlan>(std::move(current_plan), std::move(remaining_expressions));
    }
    // else current_plan stays the same
  }

  void visit(JoinPlan& join) override {
    std::vector<std::unique_ptr<LogicalPlan>> new_children;

    for (auto& child : join.children) {
      child->accept_visitor(*this);
      new_children.push_back(std::move(current_plan));
    }
    current_plan = std::make_unique<JoinPlan>(std::move(new_children), std::move(join.join_columns));
  }

  void visit(LeftOuterJoinPlan& join) override {
    join.lchild->accept_visitor(*this);
    auto new_lchild = std::move(current_plan);
    join.rchild->accept_visitor(*this);
    auto new_rchild = std::move(current_plan);
    current_plan = std::make_unique<LeftOuterJoinPlan>(
        join.alias, std::move(new_lchild), std::move(new_rchild), std::move(join.columns)
    );
  }

  void visit(RelationPlan& relation) override {
    const auto& key = std::pair(relation.alias, relation.table);
    current_plan = relation.clone();
    if (id2simple_expressions.find(key) != id2simple_expressions.end()) {
      current_plan =
          std::make_unique<SelectionPlan>(std::move(current_plan), std::move(id2simple_expressions[key]));
    }
  }

  std::unique_ptr<LogicalPlan> current_plan;

private:
  // Map from alias to a list of expressions that involve only that alias
  std::map<std::pair<std::string, std::string>, std::vector<std::unique_ptr<ExprPlan>>> id2simple_expressions;
};

} // namespace Parser::QueryRewriter

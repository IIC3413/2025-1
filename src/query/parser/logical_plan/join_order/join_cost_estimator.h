#pragma once

#include <memory>
#include <set>

#include "query/parser/logical_plan/logical_plan.h"
#include "query/parser/logical_plan/relation_plan.h"
#include "system/system.h"

class Estimator {
public:
  virtual ~Estimator() = default;

  virtual std::unique_ptr<Estimator> clone() const = 0;

  virtual double estimate_cost() const = 0;

  virtual std::set<Column> get_columns() const = 0;

  virtual std::vector<std::unique_ptr<LogicalPlan>> get_join_order() const = 0;
};

class RelationEstimator : public Estimator {
public:
  const RelationPlan* plan;
  std::set<Column> cols;

  RelationEstimator(const RelationPlan* plan, std::set<Column> cols)
      : plan(plan),
        cols(cols) {}

  std::unique_ptr<Estimator> clone() const override {
    return std::make_unique<RelationEstimator>(plan, cols);
  }

  double estimate_cost() const override {
    return catalog.get_table_cardinality(plan->table);
  }

  std::set<Column> get_columns() const override {
    return cols;
  }

  std::vector<std::unique_ptr<LogicalPlan>> get_join_order() const override {
    std::vector<std::unique_ptr<LogicalPlan>> res;
    res.push_back(plan->clone());
    return res;
  }
};

class JoinEstimator : public Estimator {
public:
  std::unique_ptr<Estimator> lhs;
  std::unique_ptr<Estimator> rhs;

  const std::vector<std::pair<Column, Column>>& join_columns;

  JoinEstimator(
      std::unique_ptr<Estimator> lhs,
      std::unique_ptr<Estimator> rhs,
      const std::vector<std::pair<Column, Column>>& join_columns
  )
      : lhs(std::move(lhs)),
        rhs(std::move(rhs)),
        join_columns(join_columns) {}

  std::unique_ptr<Estimator> clone() const override {
    return std::make_unique<JoinEstimator>(lhs->clone(), rhs->clone(), join_columns);
  }

  double estimate_cost() const override {
    double selectivity = 1.0;

    auto lhs_cols = lhs->get_columns();
    auto rhs_cols = rhs->get_columns();

    for (const auto& [c1, c2] : join_columns) {
      if ((lhs_cols.find(c1) != lhs_cols.end() && rhs_cols.find(c2) != rhs_cols.end()) ||
          (rhs_cols.find(c1) != rhs_cols.end() && lhs_cols.find(c2) != lhs_cols.end())) {
        selectivity *= 0.6;
      }
    }

    // try to avoid cross product giving extreme high cost
    if (selectivity == 1.0) {
      selectivity = 9999;
    }

    return (2 * lhs->estimate_cost() + rhs->estimate_cost()) * selectivity;
  }

  std::set<Column> get_columns() const override {
    auto res = lhs->get_columns();
    auto rhs_cols = rhs->get_columns();
    res.insert(rhs_cols.begin(), rhs_cols.end());
    return res;
  }

  std::vector<std::unique_ptr<LogicalPlan>> get_join_order() const override {
    auto res = lhs->get_join_order();
    auto rhs_order = rhs->get_join_order();

    for (auto& r : rhs_order) {
      res.push_back(std::move(r));
    }

    return res;
  }
};

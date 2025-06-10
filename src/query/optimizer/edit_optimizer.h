#pragma once

#include <memory>

#include "query/executor/query_action.h"
#include "query/parser/logical_plan/logical_plan.h"
#include "query/parser/logical_plan/logical_plan_visitor.h"

class EditOptimizer : public LogicalPlanVisitor {
public:
  static std::unique_ptr<QueryAction> create_physical_plan(std::unique_ptr<LogicalPlan>);

  void visit(CartesianProductPlan&) override {
    throw QueryException("EditOptimizer does not handle select queries.");
  }

  void visit(JoinPlan&) override {
		throw QueryException("EditOptimizer does not handle select queries.");
	}

  void visit(LeftOuterJoinPlan&) override {
		throw QueryException("EditOptimizer does not handle select queries.");
	}

  void visit(ProjectionPlan&) override {
		throw QueryException("EditOptimizer does not handle select queries.");
	}

  void visit(RelationPlan&) override {
		throw QueryException("EditOptimizer does not handle select queries.");
	}

  void visit(SelectionPlan&) override {
		throw QueryException("EditOptimizer does not handle select queries.");
	}

  void visit(CreationPlan&) override;

  void visit(InsertionPlan&) override;

private:
  std::unique_ptr<QueryAction> action;
};

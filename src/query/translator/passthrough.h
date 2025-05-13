#pragma once

#include "query/executor/query_action.h"
#include "query/parser/logical_plan/logical_plan.h"
#include "query/parser/logical_plan/logical_plan_visitor.h"
#include <memory>

class PassThrough : public LogicalPlanVisitor {
public:
  static std::unique_ptr<QueryAction> create_physical_plan(std::unique_ptr<LogicalPlan>);

  void visit(CartesianProductPlan&) override {
    throw QueryException("PassThrough does not handle select queries.");
  }

  void visit(JoinPlan&) override {
		throw QueryException("PassThrough does not handle select queries.");
	}

  void visit(LeftOuterJoinPlan&) override {
		throw QueryException("PassThrough does not handle select queries.");
	}

  void visit(ProjectionPlan&) override {
		throw QueryException("PassThrough does not handle select queries.");
	}

  void visit(RelationPlan&) override {
		throw QueryException("PassThrough does not handle select queries.");
	}

  void visit(SelectionPlan&) override {
		throw QueryException("PassThrough does not handle select queries.");
	}

  void visit(CreationPlan&) override;

  void visit(InsertionPlan&) override;

private:
  std::unique_ptr<QueryAction> action;
};

#include "edit_optimizer.h"

#include <memory>

#include "query/executor/query_action.h"
#include "query/executor/query_actions.h"
#include "query/parser/logical_plan/creation_plan.h"
#include "query/parser/logical_plan/insertion_plan.h"
#include "query/parser/logical_plan/logical_plan_visitor.h"

std::unique_ptr<QueryAction> EditOptimizer::create_physical_plan(std::unique_ptr<LogicalPlan> logical_plan) {
  EditOptimizer editor;
  logical_plan->accept_visitor(editor);
  return std::move(editor.action);
}

void EditOptimizer::visit(CreationPlan& creation) {
  action = std::make_unique<Creation>(creation.table_name, std::move(creation.schema));
}

void EditOptimizer::visit(InsertionPlan& insertion) {
  action = std::make_unique<Insertion>(insertion.table, std::move(insertion.values));
}

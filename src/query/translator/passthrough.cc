#include "passthrough.h"

#include <memory>

#include "query/executor/query_action.h"
#include "query/executor/query_actions.h"
#include "query/parser/logical_plan/creation_plan.h"
#include "query/parser/logical_plan/insertion_plan.h"
#include "query/parser/logical_plan/logical_plan_visitor.h"

std::unique_ptr<QueryAction> PassThrough::create_physical_plan(std::unique_ptr<LogicalPlan> logical_plan) {
  PassThrough editor;
  logical_plan->accept_visitor(editor);
  return std::move(editor.action);
}

void PassThrough::visit(CreationPlan& creation) {
  action = std::make_unique<Creation>(creation.table_name, std::move(creation.schema));
}

void PassThrough::visit(InsertionPlan& insertion) {
  action = std::make_unique<Insertion>(insertion.table, std::move(insertion.values));
}

#pragma once

#include "query/parser/logical_plan/logical_plan.h"
#include "query/parser/logical_plan/logical_plan_visitor.h"
#include "query/parser/query_preprocessor/query_preprocessor.h"
#include <cstdint>
#include <memory>
#include <utility>
#include <variant>
#include <vector>

class InsertionPlan : public LogicalPlan {
public:
  std::string table;
  std::vector<Constant> values;

  InsertionPlan(const std::string& table, std::vector<Constant>&& values)
    : table(table),
      values(values) {}

  void accept_visitor(LogicalPlanVisitor& visitor) override {
    visitor.visit(*this);
  }

  std::unique_ptr<LogicalPlan> clone() const override {
    std::vector<Constant> values_clone = values;
    return std::make_unique<InsertionPlan>(table, std::move(values_clone));
  }

  bool is_action() const override {
    return true;
  }

  std::ostream& print_to_ostream(std::ostream& os, int indent = 0) const override {
    os << std::string(indent, ' ');
    os << "Insertion(";
    os << table;
    for (size_t i = 0; i < values.size(); i++) {
      if (std::holds_alternative<int64_t>(values[i])) {
        os << ", " << std::get<int64_t>(values[i]);
      } else {
        os << ", " << std::get<std::string>(values[i]);
      }
    }
    return os << ")\n";
  }
};

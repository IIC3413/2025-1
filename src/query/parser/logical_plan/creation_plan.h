#pragma once

#include "query/parser/logical_plan/logical_plan.h"
#include "query/parser/logical_plan/logical_plan_visitor.h"
#include "relational_model/schema.h"
#include <memory>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

class CreationPlan : public LogicalPlan {
public:
  std::string table_name;
  Schema schema;

  CreationPlan(const std::string& table_name, Schema&& schema)
    : table_name(table_name),
      schema(schema) {}

  void accept_visitor(LogicalPlanVisitor& visitor) override {
    visitor.visit(*this);
  }

  std::unique_ptr<LogicalPlan> clone() const override {
    Schema schema_clone = schema;
    return std::make_unique<CreationPlan>(table_name, std::move(schema_clone));
  }

  bool is_action() const override {
    return true;
  }

  std::ostream& print_to_ostream(std::ostream& os, int indent = 0) const override {
    os << std::string(indent, ' ');
    os << "Creation(";
    os << table_name;
    for (size_t i = 0; i < schema.columns.size(); i++) {
      os << ", " << schema.columns[i].name << ":";
      if (schema.columns[i].datatype == DataType::STR) {
        os << "STR";
      } else {
        os << "INT";
      }
    }
    return os << ")\n";
  }
};

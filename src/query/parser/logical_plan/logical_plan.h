#pragma once

#include <memory>
#include <ostream>
#include <string>

#include "logical_plan_visitor.h"
#include "relational_model/schema.h"

class Column {
public:
  const std::string alias;
  const std::string table;
  const ColumnInfo info;

  Column(const std::string& alias, const std::string& table, const ColumnInfo& info)
      : alias(alias),
        table(table),
        info(info) {}

  bool operator==(const Column& other) const {
    // not considering datatype as it is defined by alias and column.
    return alias == other.alias && info.name == other.info.name;
  }

  bool operator<(const Column& other) const {
    // not considering datatype as it is defined by alias and column.
    if (alias < other.alias) {
      return true;
    } else if (other.alias < alias) {
      return false;
    } else {
      return info.name < other.info.name;
    }
  }

  bool operator!=(const Column& other) const {
    return !(*this == other);
  }
};

class LogicalPlan {
public:
  virtual ~LogicalPlan() = default;

  virtual void accept_visitor(LogicalPlanVisitor& visitor) = 0;

  virtual std::unique_ptr<LogicalPlan> clone() const = 0;

  virtual std::ostream& print_to_ostream(std::ostream& os, int indent = 0) const = 0;

  virtual bool is_action() const = 0;

  friend std::ostream& operator<<(std::ostream& os, const LogicalPlan& node) {
    return node.print_to_ostream(os);
  }
};

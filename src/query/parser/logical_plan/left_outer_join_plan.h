#pragma once

#include <cassert>
#include <iostream>
#include <memory>
#include <ostream>
#include <vector>

#include "query/parser/logical_plan/logical_plan.h"
#include "query/parser/logical_plan/logical_plan_visitor.h"
#include "query/parser/logical_plan/relation_plan.h"

class LeftOuterJoinPlan : public LogicalPlan {
public:
  std::string alias;
  std::unique_ptr<LogicalPlan> lchild;
  std::unique_ptr<LogicalPlan> rchild;
  std::vector<std::pair<Column, Column>> columns;

  LeftOuterJoinPlan(
      const std::string& alias,
      std::unique_ptr<LogicalPlan> _lchild,
      std::unique_ptr<LogicalPlan> _rchild,
      std::vector<std::pair<Column, Column>>&& columns
  )
      : alias(alias),
        lchild(std::move(_lchild)),
        rchild(std::move(_rchild)),
        columns(columns) {
    assert(columns.size() >= 1 && "There must be at least one ON condition");
  }

  void accept_visitor(LogicalPlanVisitor& visitor) override {
    visitor.visit(*this);
  }

  std::unique_ptr<LogicalPlan> clone() const override {
    auto columns_clone = columns;
    return std::make_unique<LeftOuterJoinPlan>(
        alias, std::unique_ptr<RelationPlan>(static_cast<RelationPlan*>(lchild->clone().release())),
        std::unique_ptr<RelationPlan>(static_cast<RelationPlan*>(rchild->clone().release())),
        std::move(columns_clone)
    );
  }

  bool is_action() const override {
    return false;
  }

  std::ostream& print_to_ostream(std::ostream& os, int indent = 0) const override {
    os << std::string(indent, ' ');
    os << "LeftOuterJoin(";
    os << columns[0].first.table << "." << columns[0].first.info.name;
    os << " == ";
    os << columns[0].second.table << "." << columns[0].second.info.name;
    for (size_t i = 1; i < columns.size(); ++i) {
      os << " AND ";
      os << columns[i].first.table << "." << columns[i].first.info.name;
      os << " == ";
      os << columns[i].second.table << "." << columns[i].second.info.name;
    }
    os << ") AS " << alias << "\n";
    lchild->print_to_ostream(os, indent + 2);
    rchild->print_to_ostream(os, indent + 2);
    return os;
  }
};

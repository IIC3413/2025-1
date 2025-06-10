#pragma once

#include <cassert>

#include "query/executor/query_iter.h"

class CartesianProduct : public QueryIter {
public:
  CartesianProduct(
      std::unique_ptr<QueryIter> _lhs,
      std::unique_ptr<QueryIter> _rhs,
      std::vector<ProjectedColumn>&& _projected_lhs_columns,
      std::vector<ProjectedColumn>&& _projected_rhs_columns
  )
      : lhs(std::move(_lhs)),
        rhs(std::move(_rhs)),
        projected_lhs_columns(std::move(_projected_lhs_columns)),
        projected_rhs_columns(std::move(_projected_rhs_columns)),
        lhs_out(lhs->get_output()),
        rhs_out(rhs->get_output()),
        out(projected_lhs_columns.size() + projected_rhs_columns.size()) {

    for (size_t i = 0; i < projected_lhs_columns.size(); i++) {
      out.values[i] = lhs_out.values[projected_lhs_columns[i].pos];
    }
    size_t offset = projected_lhs_columns.size();
    for (size_t i = 0; i < projected_rhs_columns.size(); i++) {
      out.values[offset + i] = rhs_out.values[projected_rhs_columns[i].pos];
    }
  }

  void begin() override {
    lhs->begin();
    rhs->begin();

    valid_lhs = false;
  }

  // simple nested loop join
  bool next() override {
    while (true) {
      if (valid_lhs) {
        if (rhs->next()) {
          return true;
        } else {
          valid_lhs = false;
        }
      } else {
        if (lhs->next()) {
          valid_lhs = true;
          rhs->reset();
        } else {
          return false;
        }
      }
    }
    return false;
  }

  void reset() override {
    lhs->reset();
    rhs->reset();
  }

  RecordRef& get_output() override {
    return out;
  }

  std::vector<Column> get_columns() override {
    std::vector<Column> res;
    for (auto& c : projected_lhs_columns) {
      res.push_back(c.col);
    }
    for (auto& c : projected_rhs_columns) {
      res.push_back(c.col);
    }
    return res;
  }

  std::ostream& print_to_ostream(std::ostream& os, int indent = 0) const override {
    os << std::string(indent, ' ');
    os << "CartesianProduct()\n";
    lhs->print_to_ostream(os, indent + 2);
    rhs->print_to_ostream(os, indent + 2);
    return os;
  }

private:
  std::unique_ptr<QueryIter> lhs;
  std::unique_ptr<QueryIter> rhs;
  std::vector<ProjectedColumn> projected_lhs_columns;
  std::vector<ProjectedColumn> projected_rhs_columns;
  RecordRef& lhs_out;
  RecordRef& rhs_out;
  RecordRef out;
  bool valid_lhs;
};

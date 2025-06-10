#pragma once

#include <cassert>

#include "query/executor/query_iter.h"
#include "relational_model/schema.h"

class LeftOuterJoin : public QueryIter {
public:
  LeftOuterJoin(
      std::unique_ptr<QueryIter> _lhs,
      std::unique_ptr<QueryIter> _rhs,
      std::vector<ProjectedColumn>&& _projected_lhs_columns,
      std::vector<ProjectedColumn>&& _projected_rhs_columns,
      std::vector<std::pair<size_t, size_t>>&& _equalities
  )
      : lhs(std::move(_lhs)),
        rhs(std::move(_rhs)),
        projected_lhs_columns(std::move(_projected_lhs_columns)),
        projected_rhs_columns(std::move(_projected_rhs_columns)),
        equalities(std::move(_equalities)),
        lhs_out(lhs->get_output()),
        rhs_out(rhs->get_output()),
        out(projected_lhs_columns.size() + projected_rhs_columns.size()) {
    assert(equalities.size() > 0);
    init_rhs_null();
    init_refs();
  }

  void begin() override {
    lhs->begin();
    rhs->begin();
    valid_lhs = false;
  }

  bool next() override {
    // TODO: not available, students still may have ticket for late lab3
    return false;
  }

  void reset() override {
    lhs->reset();
    rhs->reset();
    valid_lhs = false;
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
    os << "LeftOuterJoin (";
    os << projected_lhs_columns[equalities[0].first].col.alias << "."
       << projected_lhs_columns[equalities[0].first].col.info.name;
    os << " == ";
    os << projected_rhs_columns[equalities[0].second].col.alias << "."
       << projected_rhs_columns[equalities[0].second].col.info.name;
    for (size_t i = 1; i < equalities.size(); ++i) {
      os << " AND ";
      os << projected_lhs_columns[equalities[i].first].col.alias << "."
         << projected_lhs_columns[equalities[i].first].col.info.name;
      os << " == ";
      os << projected_rhs_columns[equalities[i].second].col.alias << "."
         << projected_rhs_columns[equalities[i].second].col.info.name;
    }
    os << ")\n";
    lhs->print_to_ostream(os, indent + 2);
    rhs->print_to_ostream(os, indent + 2);
    return os;
  }

private:
  std::unique_ptr<QueryIter> lhs;
  std::unique_ptr<QueryIter> rhs;

  std::vector<ProjectedColumn> projected_lhs_columns;
  std::vector<ProjectedColumn> projected_rhs_columns;

  std::vector<std::pair<size_t, size_t>> equalities;

  RecordRef& lhs_out;
  RecordRef& rhs_out;

  RecordRef out;

  std::unique_ptr<Record> rhs_buffer;

  bool valid_lhs;

  bool outer_match;

  std::vector<Value> rhs_null_values;

  void init_refs() {
    std::vector<DataType> rhs_datatypes;
    for (auto& rhs_projected_column : projected_rhs_columns) {
      rhs_datatypes.push_back(rhs_projected_column.col.info.datatype);
    }
    rhs_buffer = std::make_unique<Record>(std::move(rhs_datatypes));


    for (size_t i = 0; i < projected_lhs_columns.size(); i++) {
      out.values[i] = lhs_out.values[projected_lhs_columns[i].pos];
    }
    size_t offset = projected_lhs_columns.size();
    for (size_t i = 0; i < projected_rhs_columns.size(); i++) {
      out.values[offset + i] = &rhs_buffer->values[i];
    }
  }

  void init_rhs_null() {
    for (const auto& c : projected_rhs_columns) {
      switch (c.col.info.datatype) {
      case DataType::INT:
        rhs_null_values.push_back(Value(-1));
        break;
      case DataType::STR:
        rhs_null_values.push_back(Value("-1"));
        break;
      }
    }
  }

  void set_output_match() {
    for (size_t i = 0; i < projected_rhs_columns.size(); i++) {
      rhs_buffer->values[i] = *rhs_out.values[projected_rhs_columns[i].pos];
    }
  }

  void set_output_null() {
    for (size_t i = 0; i < projected_rhs_columns.size(); i++) {
      rhs_buffer->values[i] = rhs_null_values[i];
    }
  }
};

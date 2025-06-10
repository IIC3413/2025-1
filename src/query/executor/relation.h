#pragma once

#include "query/executor/query_iter.h"
#include "relational_model/relation_iter.h"

class Relation : public QueryIter {
public:
  Relation(
      std::unique_ptr<RelationIter> _child,
      const Schema& _relation_schema,
      std::vector<ProjectedColumn>&& _projected_columns
  )
      : child(std::move(_child)),
        projected_columns(std::move(_projected_columns)),
        child_out(_relation_schema),
        out(projected_columns.size()) {
    for (size_t i = 0; i < projected_columns.size(); i++) {
      out.values[i] = &child_out.values[projected_columns[i].pos];
    }
  }

  void begin() override {
    child->begin(child_out);
  }

  bool next() override {
    return (child->next());
  }

  void reset() override {
    child->reset();
  }

  RecordRef& get_output() override {
    return out;
  }

  std::vector<Column> get_columns() override {
    std::vector<Column> res;
    for (const auto& c : projected_columns) {
      res.push_back(c.col);
    }
    return res;
  }

  std::ostream& print_to_ostream(std::ostream& os, int indent = 0) const override {
    os << std::string(indent, ' ');
    os << "Relation(";
    if (projected_columns.size() > 0) {
      os << projected_columns[0].col.table;
      if (projected_columns[0].col.table != projected_columns[0].col.alias) {
        os << " as " << projected_columns[0].col.alias;
      }
    }
    os << ")\n";
    return os;
  }

private:
  std::unique_ptr<RelationIter> child;
  std::vector<ProjectedColumn> projected_columns;
  Record child_out;
  RecordRef out;
};

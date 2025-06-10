#include "hash_join.h"

#include <cassert>
#include <set>

HashJoin::HashJoin(
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
      rhs_out(rhs->get_output()),
      out(projected_lhs_columns.size() + projected_rhs_columns.size()),
      bloom_filter(512, 4) {

  assert(equalities.size() > 0);

  std::vector<DataType> lsh_buffer_datatypes;

  std::set<Column> join_columns_set;
  for (auto&& [idx_lhs, idx_rhs] : equalities) {
    lsh_buffer_datatypes.push_back(projected_lhs_columns[idx_lhs].col.info.datatype);
    join_lhs_columns.push_back(projected_lhs_columns[idx_lhs]);
    join_rhs_columns.push_back(projected_rhs_columns[idx_rhs]);

    auto& join_column = projected_lhs_columns[idx_lhs].col;
    join_columns_set.insert(join_column);
  }

  for (auto& lhs_projected_column : projected_lhs_columns) {
    if (join_columns_set.find(lhs_projected_column.col) == join_columns_set.end()) {
      nonjoin_lhs_columns.push_back(lhs_projected_column);
      lsh_buffer_datatypes.push_back(lhs_projected_column.col.info.datatype);
    }
  }

  for (auto& rhs_projected_column : projected_rhs_columns) {
    if (join_columns_set.find(rhs_projected_column.col) == join_columns_set.end()) {
      nonjoin_rhs_columns.push_back(rhs_projected_column);
    }
  }

  lhs_buffer = std::make_unique<Record>(std::move(lsh_buffer_datatypes));

  for (size_t i = 0; i < projected_lhs_columns.size(); i++) {
    out.values[i] = &lhs_buffer->values[i];
  }

  size_t offset = projected_lhs_columns.size();
  for (size_t i = 0; i < projected_rhs_columns.size(); i++) {
    out.values[offset + i] = rhs_out.values[projected_rhs_columns[i].pos];
  }
}

void HashJoin::begin() {
  lhs->begin();
  rhs->begin();

  fill();
}

void HashJoin::reset() {
  lhs->reset();
  rhs->reset();

  hash_table.clear();
  fill();
}

void HashJoin::fill() {
  auto& lhs_out = lhs->get_output();

  while (lhs->next()) {
    std::vector<Value> lhs_join_values;
    std::vector<Value> lhs_nonjoin_values;

    for (const auto& join_lhs_column : join_lhs_columns) {
      lhs_join_values.push_back(*lhs_out.values[join_lhs_column.pos]);
    }

    for (const auto& nonjoin_lhs_column : nonjoin_lhs_columns) {
      lhs_nonjoin_values.push_back(*lhs_out.values[nonjoin_lhs_column.pos]);
    }

    Record join_record(std::move(lhs_join_values));

    // hash_table.emplace creates a new tuple only if the key was not in the map
    // if the key was on the map, nothing is inserted but we get the pointer to the
    // record (it is the iterator that points to that record)
    auto&& [it, _] = hash_table.emplace(std::move(join_record), std::vector<Record>());
    it->second.push_back(Record(std::move(lhs_nonjoin_values)));
  }
}

bool HashJoin::next() {
  while (rhs->next()) {
    std::vector<Value> rhs_join_values;
    for (const auto& join_rhs_column : join_rhs_columns) {
      rhs_join_values.push_back(*rhs_out.values[join_rhs_column.pos]);
    }
    Record rhs_key(std::move(rhs_join_values));

    if (!bloom_filter.might_contain(rhs_key.hash())) {
      continue;
    }

    auto it = hash_table.find(rhs_key);
    if (it != hash_table.end()) {
      const Record& current_key = it->first;
      auto current_vector = &it->second;
      auto vector_iter = current_vector->begin();

      for (size_t i = 0; i < join_lhs_columns.size(); i++) {
        lhs_buffer->values[i] = current_key.values[i];
      }
      size_t offset = join_lhs_columns.size();
      for (size_t i = 0; i < nonjoin_lhs_columns.size(); i++) {
        lhs_buffer->values[i + offset] = vector_iter->values[i];
      }
      vector_iter++;
      return true;
    }
  }
  return false;
}

RecordRef& HashJoin::get_output() {
  return out;
}

std::vector<Column> HashJoin::get_columns() {
  std::vector<Column> res;
  for (auto& c : join_lhs_columns) {
    res.push_back(c.col);
  }
  for (auto& c : nonjoin_lhs_columns) {
    res.push_back(c.col);
  }
  for (auto& c : projected_rhs_columns) {
    res.push_back(c.col);
  }
  return res;
}

std::ostream& HashJoin::print_to_ostream(std::ostream& os, int indent) const {
  os << std::string(indent, ' ');
  os << "HashJoin(";
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

#pragma once

#include <unordered_map>

#include "query/executor/bloom_filter/bloom_filter.h"
#include "query/executor/query_iter.h"

class HashJoin : public QueryIter {
public:
  HashJoin(
      std::unique_ptr<QueryIter> _lhs,
      std::unique_ptr<QueryIter> _rhs,
      std::vector<ProjectedColumn>&& _projected_lhs_columns,
      std::vector<ProjectedColumn>&& _projected_rhs_columns,
      std::vector<std::pair<size_t, size_t>>&& _equalities
  );

  void begin() override;

  bool next() override;

  void reset() override;

  RecordRef& get_output() override;

  std::vector<Column> get_columns() override;

  std::ostream& print_to_ostream(std::ostream& os, int indent = 0) const override;

private:
  std::unique_ptr<QueryIter> lhs;
  std::unique_ptr<QueryIter> rhs;

  std::vector<ProjectedColumn> projected_lhs_columns;
  std::vector<ProjectedColumn> projected_rhs_columns;

  std::vector<std::pair<size_t, size_t>> equalities;

  std::vector<ProjectedColumn> join_lhs_columns;
  std::vector<ProjectedColumn> join_rhs_columns;
  std::vector<ProjectedColumn> nonjoin_lhs_columns;
  std::vector<ProjectedColumn> nonjoin_rhs_columns;

  std::unordered_map<Record, std::vector<Record>, Record::Hasher> hash_table;

  std::unique_ptr<Record> lhs_buffer;

  RecordRef& rhs_out;

  RecordRef out;

  BloomFilter bloom_filter;

  void fill();
};

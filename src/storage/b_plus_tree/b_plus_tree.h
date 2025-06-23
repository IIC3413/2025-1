#pragma once

#include <memory>

#include "relational_model/index.h"
#include "storage/b_plus_tree/b_plus_tree_dir.h"
#include "storage/heap_file/heap_file.h"

class BPlusTree : public Index {
public:
  BPlusTree(const HeapFile& heap_file, int key_col_idx, FileId dir_file_id, FileId leaf_file_id);

  void insert_record(RID rid) override;

  void delete_record(RID rid) override;

  std::unique_ptr<RelationIter> get_iter(const Value& min, const Value& max) override;

  IndexType get_type() override {
    return IndexType::B_PLUS_TREE;
  }

  int get_key_column_idx() override {
    return key_column_idx;
  }

  const HeapFile& heap_file;

  const int key_column_idx;

  const FileId dir_file_id;

  const FileId leaf_file_id;

  // we reuse this attribute in inserts/deletes to reduce allocations
  Record record_buf;

  std::unique_ptr<BPlusTreeDir> root;
};

#include "b_plus_tree.h"

#include "storage/b_plus_tree/b_plus_tree_dir.h"
#include "storage/b_plus_tree/b_plus_tree_iter.h"
#include "storage/heap_file/heap_file.h"
#include "storage/heap_file/heap_file_iter.h"

// construct 8 byte integer with first 8 characters
int64_t serialize_string_key(const char* str) {
  int64_t res = 0;

  int shift_size = 8 * 7;
  for (int i = 0; i < 8 && *str != '\0'; i++, str++, shift_size -= 8) {
    int64_t byte64 = static_cast<int64_t>(*str);
    res |= byte64 << shift_size;
  }

  return res;
}

BPlusTree::BPlusTree(const HeapFile& heap_file, int key_column_idx, FileId dir_file_id, FileId leaf_file_id)
    : heap_file(heap_file),
      key_column_idx(key_column_idx),
      dir_file_id(dir_file_id),
      leaf_file_id(leaf_file_id),
      record_buf(heap_file.schema) {
  root = std::make_unique<BPlusTreeDir>(*this, 0);
  if (root->get_child_count() == 0) {
    // the B+tree is new, initialize empty
    root->set_child_count(1);
  }
}

std::unique_ptr<RelationIter> BPlusTree::get_iter(const Value& min, const Value& max) {
  int64_t encoded_min;
  int64_t encoded_max;

  auto key_datatype = heap_file.schema.columns[key_column_idx].datatype;
  switch (key_datatype) {
  case DataType::STR: {
    encoded_min = serialize_string_key(min.value.as_str);
    encoded_max = serialize_string_key(max.value.as_str);
    break;
  }

  case DataType::INT: {
    encoded_min = min.value.as_int;
    encoded_max = max.value.as_int;
    break;
  }
  }

  BPlusTreeRecord min_record(encoded_min, RID(INT32_MIN, INT32_MIN));
  BPlusTreeRecord max_record(encoded_max, RID(INT32_MAX, INT32_MAX));

  return std::make_unique<BPlusTreeIter>(*this, min, max, key_column_idx, min_record, max_record);
}

void BPlusTree::insert_record(RID rid) {
  heap_file.get_record(rid, record_buf);
  auto key = record_buf.values[key_column_idx];

  auto key_datatype = heap_file.schema.columns[key_column_idx].datatype;
  switch (key_datatype) {
  case DataType::STR: {
    root->insert_record(BPlusTreeRecord(serialize_string_key(key.value.as_str), rid));
    break;
  }

  case DataType::INT: {
    root->insert_record(BPlusTreeRecord(key.value.as_int, rid));
    break;
  }
  }
}

void BPlusTree::delete_record(RID rid) {
  heap_file.get_record(rid, record_buf);
  auto key = record_buf.values[key_column_idx];

  auto key_datatype = heap_file.schema.columns[key_column_idx].datatype;
  switch (key_datatype) {
  case DataType::STR: {
    root->delete_record(BPlusTreeRecord(serialize_string_key(key.value.as_str), rid));
    break;
  }

  case DataType::INT: {
    root->delete_record(BPlusTreeRecord(key.value.as_int, rid));
    break;
  }
  }
}

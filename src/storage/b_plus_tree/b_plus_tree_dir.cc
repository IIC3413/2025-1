#include "b_plus_tree_dir.h"

#include "storage/b_plus_tree/b_plus_tree.h"
#include "storage/b_plus_tree/b_plus_tree_leaf.h"
#include "storage/b_plus_tree/b_plus_tree_utils.h"
#include "system/system.h"

BPlusTreeDir::BPlusTreeDir(const BPlusTree& bpt, int32_t page_number)
    : bpt(bpt),
      page(buffer_mgr.get_page(bpt.dir_file_id, page_number)) {}

BPlusTreeDir::BPlusTreeDir(const BPlusTree& bpt)
    : bpt(bpt),
      page(buffer_mgr.append_page(bpt.dir_file_id)) {}

BPlusTreeDir::~BPlusTreeDir() {
  page.unpin();
}

int32_t BPlusTreeDir::get_child_count() const {
  return page.read_int32(OFFSET_CHILD_COUNT);
}

void BPlusTreeDir::set_child_count(int32_t child_count) {
  page.write_int32(OFFSET_CHILD_COUNT, child_count);
}

// valid index goes from [0, get_child_count() - 1]
int32_t BPlusTreeDir::get_child(size_t index) const {
  return page.read_int32(OFFSET_CHILDREN + sizeof(child_t) * index);
}

void BPlusTreeDir::set_child(size_t index, int32_t child) {
  page.write_int32(OFFSET_CHILDREN + sizeof(child_t) * index, child);
}

// valid index goes from [0, get_child_count() - 2]
BPlusTreeRecord BPlusTreeDir::get_record(size_t index) const {
  auto offset = OFFSET_RECORD + index * sizeof(BPlusTreeRecord);
  auto encoded_key = page.read_int64(offset);
  auto page_num = page.read_int32(offset + 8);
  auto dir_slot = page.read_int32(offset + 12);
  return BPlusTreeRecord(encoded_key, RID(page_num, dir_slot));
}

void BPlusTreeDir::set_record(size_t index, const BPlusTreeRecord& record) {
  auto offset = OFFSET_RECORD + index * sizeof(BPlusTreeRecord);
  page.write_int64(offset, record.encoded_key);
  page.write_int32(offset + 8, record.rid.page_num);
  page.write_int32(offset + 12, record.rid.dir_slot);
}

BPlusTreeSearchResult BPlusTreeDir::search_leaf(const BPlusTreeRecord& record) {
  auto dir_index = search_child_idx(record);
  auto page_num = get_child(dir_index);

  if (page_num < 0) { // negative number: pointer to dir
    BPlusTreeDir child(bpt, -1 * page_num);
    return child.search_leaf(record);
  } else { // positive number: pointer to leaf
    BPlusTreeLeaf child(bpt, page_num);
    auto index = child.search_index(record);
    return BPlusTreeSearchResult(page_num, index);
  }
}

int32_t BPlusTreeDir::search_child_idx(const BPlusTreeRecord& record) {
  auto from = 0;
  auto to = get_child_count() - 1;

  while (from != to) {
    auto middle_idx = ((from + to + 1) / 2) - 1;
    if (record < get_record(middle_idx)) {
      to = middle_idx;
    } else {
      from = middle_idx + 1;
    }
  }

  return from;
}

void BPlusTreeDir::delete_record(const BPlusTreeRecord& record) {
  auto dir_index = search_child_idx(record);
  auto page_pointer = get_child(dir_index);

  if (page_pointer < 0) { // negative number: pointer to dir
    BPlusTreeDir child(bpt, -1 * page_pointer);
    child.delete_record(record);
  } else { // positive number: pointer to leaf
    BPlusTreeLeaf child(bpt, page_pointer);
    child.delete_record(record);
  }
}

std::unique_ptr<BPlusTreeSplit> BPlusTreeDir::insert_record(const BPlusTreeRecord& record) {
  auto child_count = get_child_count();
  assert(child_count >= 1);
  auto record_count = child_count - 1;

  auto dir_index = record_count > 0 ? search_child_idx(record) : 0;
  auto page_pointer = get_child(dir_index);

  std::unique_ptr<BPlusTreeSplit> split = nullptr;

  if (page_pointer < 0) {
    // negative number: pointer to dir
    BPlusTreeDir child(bpt, -1 * page_pointer);
    split = child.insert_record(record);
  } else {
    // positive number: pointer to leaf
    BPlusTreeLeaf child(bpt, page_pointer);
    split = child.insert_record(record);
  }

  if (split != nullptr) {
    auto split_child_idx = search_child_idx(split->record);

    // Case 1: no need to split this node
    if (record_count < max_records) {
      // shift right records and children
      for (int i = record_count; i >= split_child_idx; i--) {
        set_record(i, get_record(i - 1));
        set_child(i + 1, get_child(i));
      }

      set_record(split_child_idx, split->record);
      set_child(split_child_idx + 1, split->encoded_page_number);
      set_child_count(child_count + 1);
    }
    // Case 2: we need to split this node and this node is not the root
    else if (page.get_page_number() != 0) {
      auto last_record = get_record(max_records - 1);
      auto last_child = get_child(max_children - 1);

      if (split_child_idx == max_children - 1) {
        last_record = split->record;
        last_child = split->encoded_page_number;
      } else {
        // shift and insert
        for (int i = max_records - 1; i > split_child_idx; i--) {
          set_record(i, get_record(i - 1));
          set_child(i + 1, get_child(i));
        }
        set_record(split_child_idx, split->record);
        set_child(split_child_idx + 1, split->encoded_page_number);
      }
      constexpr auto middle_index = (max_records + 1) / 2;

      BPlusTreeDir new_dir(bpt);

      // write records from (middle_index+1) to the end and the last record saved before
      // write children from (middle_index+1) to the end and the last child saved before
      auto split_record = get_record(middle_index);
      int j = 0;
      for (int i = middle_index + 1; i < max_records; i++, j++) {
        new_dir.set_child(j, this->get_child(i));
        new_dir.set_record(j, this->get_record(i));
      }
      new_dir.set_child(j, this->get_child(max_children - 1));
      new_dir.set_child(j + 1, last_child);
      new_dir.set_record(j, last_record);

      // update counts
      this->set_child_count(middle_index + 1);
      new_dir.set_child_count((max_children + 1) - (middle_index + 1));

      // key at middle_index is returned
      return std::make_unique<BPlusTreeSplit>(split_record, -1 * new_dir.page.get_page_number());
    }
    // Case 3: root split
    else {
      auto last_record = get_record(max_records - 1);
      auto last_child = get_child(max_children - 1);

      if (split_child_idx == max_children - 1) {
        last_record = split->record;
        last_child = split->encoded_page_number;
      } else {
        // shift and insert
        for (int i = max_records - 1; i > split_child_idx; i--) {
          set_record(i, get_record(i - 1));
          set_child(i + 1, get_child(i));
        }
        set_record(split_child_idx, split->record);
        set_child(split_child_idx + 1, split->encoded_page_number);
      }
      constexpr auto middle_index = (max_records + 1) / 2;

      BPlusTreeDir new_lhs_dir(bpt);
      BPlusTreeDir new_rhs_dir(bpt);

      // write left records from 0 to (middle_index-1)
      // write left children from 0 to middle_index
      for (int i = 0; i < middle_index; i++) {
        new_lhs_dir.set_child(i, this->get_child(i));
        new_lhs_dir.set_record(i, this->get_record(i));
      }
      auto split_record = get_record(middle_index);
      new_lhs_dir.set_child(middle_index, this->get_child(middle_index));

      // write right records from (middle_index+1) to the end and the last record saved before
      // write right children from (middle_index+1) to the end and the last child saved before
      int j = 0;
      for (int i = middle_index + 1; i < max_records; i++, j++) {
        new_rhs_dir.set_child(j, this->get_child(i));
        new_rhs_dir.set_record(j, this->get_record(i));
      }
      new_rhs_dir.set_child(j, this->get_child(max_children - 1));
      new_rhs_dir.set_child(j + 1, last_child);
      new_rhs_dir.set_record(j, last_record);

      // update counts
      new_lhs_dir.set_child_count(middle_index + 1);
      new_rhs_dir.set_child_count((max_children + 1) - (middle_index + 1));

      this->set_child_count(2);
      this->set_child(0, new_lhs_dir.page.get_page_number() * -1);
      this->set_child(1, new_rhs_dir.page.get_page_number() * -1);
      this->set_record(0, split_record);
    }
  }

  return nullptr;
}

#include "b_plus_tree_leaf.h"

#include "system/system.h"

BPlusTreeLeaf::BPlusTreeLeaf(const BPlusTree& bpt, int32_t page_number)
    : bpt(bpt),
      page(buffer_mgr.get_page(bpt.leaf_file_id, page_number)) {}

BPlusTreeLeaf::BPlusTreeLeaf(const BPlusTree& bpt)
    : bpt(bpt),
      page(buffer_mgr.append_page(bpt.leaf_file_id)) {}

BPlusTreeLeaf::~BPlusTreeLeaf() {
  page.unpin();
}

std::unique_ptr<BPlusTreeSplit> BPlusTreeLeaf::insert_record(const BPlusTreeRecord& record) {
  const auto record_count = get_record_count();

  // border case, needs to be handled differently
  if (record_count == 0) {
    set_record(0, record);
    set_record_count(1);
    return nullptr;
  }
  auto index = search_index(record);

  // avoid inserting duplicated record
  if (index < max_records && get_record(index) == record) {
    return nullptr;
  }

  if (record_count < max_records) {
    // shift right record 1 position from `index` to the end
    for (auto i = record_count - 1; i >= index; i--) {
      set_record(i + 1, get_record(i));
    }

    set_record(index, record);
    set_record_count(record_count + 1);
    return nullptr;
  } else {
    // put new record and save the last (that does not fit)
    BPlusTreeRecord last_record = get_record(max_records - 1);
    if (index == max_records) {
      last_record = record;
    } else {
      // shift right records 1 position from `index` to the penultimate record
      for (auto i = record_count - 2; i >= index; i--) {
        set_record(i + 1, get_record(i));
      }
      set_record(index, record);
    }

    // create new leaf to be between this old leaf and the old next
    BPlusTreeLeaf new_leaf(bpt);
    new_leaf.set_next_page_number(get_next_page_number());

    set_next_page_number(new_leaf.page.get_page_number());

    constexpr auto middle_index = (max_records + 1) / 2;

    for (int i = middle_index, j = 0; i < max_records; i++, j++) {
      new_leaf.set_record(j, get_record(i));
    }
    new_leaf.set_record((max_records / 2), last_record);

    // update counts
    set_record_count(middle_index);
    new_leaf.set_record_count((max_records / 2) + 1);

    auto split_record = new_leaf.get_record(0);

    return std::make_unique<BPlusTreeSplit>(split_record, new_leaf.page.get_page_number());
  }
}

void BPlusTreeLeaf::delete_record(const BPlusTreeRecord& record) {
  const auto record_count = get_record_count();
  if (record_count == 0) {
    return;
  }
  auto index = search_index(record);

  if (index < max_records && get_record(index) == record) {
    // shift left records 1 position from `index` to the end
    for (auto i = index + 1; i < record_count; i++) {
      set_record(i - 1, get_record(i));
    }
    set_record_count(record_count - 1);
  }
}

int32_t BPlusTreeLeaf::get_record_count() const {
  return page.read_int32(OFFSET_RECORD_COUNT);
}

void BPlusTreeLeaf::set_record_count(int32_t record_count) {
  page.write_int32(0, record_count);
}

int32_t BPlusTreeLeaf::get_next_page_number() const {
  return page.read_int32(OFFSET_NEXT_LEAF);
}

void BPlusTreeLeaf::set_next_page_number(int32_t n) {
  page.write_int32(4, n);
}

BPlusTreeRecord BPlusTreeLeaf::get_record(int32_t idx) const {
  auto offset = OFFSET_RECORDS + idx * sizeof(BPlusTreeRecord);
  auto key = page.read_int64(offset);
  auto page_num = page.read_int32(offset + 8);
  auto dir_slot = page.read_int32(offset + 12);
  return BPlusTreeRecord(key, RID(page_num, dir_slot));
}

void BPlusTreeLeaf::set_record(int32_t idx, const BPlusTreeRecord& record) {
  auto offset = OFFSET_RECORDS + idx * sizeof(BPlusTreeRecord);
  page.write_int64(offset, record.encoded_key);
  page.write_int32(offset + 8, record.rid.page_num);
  page.write_int32(offset + 12, record.rid.dir_slot);
}

int32_t BPlusTreeLeaf::search_index(const BPlusTreeRecord& record) const {
  auto from = 0;
  auto to = get_record_count() - 1;

  while (from < to) {
    auto mid = (from + to) / 2;

    auto mid_record = get_record(mid);
    if (record < mid_record) {
      to = mid - 1;
      continue;
    } else if (mid_record < record) {
      from = mid + 1;
      continue;
    }
    // record is equal
    return mid;
  }
  // from >= to
  if (get_record(from) < record) {
    return from + 1;
  } else {
    return from;
  }
}

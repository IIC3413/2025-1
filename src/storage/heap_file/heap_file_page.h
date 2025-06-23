#pragma once

#include <cstdint>

#include "relational_model/record.h"
#include "storage/heap_file/rid.h"
#include "storage/page.h"

class HeapFilePage {
public:
  Page& page;

  HeapFilePage(FileId file_id, int64_t page_number);

  ~HeapFilePage();

  // returns true if record was inserted, false if no space available
  // when the function returns true, the out_record_id is setted
  bool try_insert_record(const Record& record, RID* out_record_id);

  void vacuum(const Schema& schema);

  // returns false if dir_pos is marked as deleted
  // return true and writes the record in out otherwise
  bool get_record(int32_t dir_pos, Record& out) const;

  void edit_record(int32_t dir_pos, const Record& record);

  void delete_record(int32_t dir_pos);

  int32_t get_dir_count() const;

  int32_t get_free_space() const;

  int32_t get_dir(int32_t idx) const;

private:
  void set_dir_count(int32_t new_dir_count);

  void set_free_space(int32_t new_free_space);

  void set_dir(int32_t idx, int32_t new_dir_value);
};

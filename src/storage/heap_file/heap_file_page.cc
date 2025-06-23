#include "heap_file_page.h"

#include <cstdint>
#include <cstring>

#include "relational_model/record.h"
#include "storage/page.h"
#include "system/system.h"

HeapFilePage::HeapFilePage(FileId file_id, int64_t page_number)
    : page(buffer_mgr.get_page(file_id, page_number)) {
  // if new page, initialize to be valid
  // new pages comes with all bytes setted at 0
  if (get_dir_count() == 0 && get_free_space() == 0) {
    set_free_space(Page::SIZE - 2 * sizeof(int32_t));
  }
}

HeapFilePage::~HeapFilePage() {
  page.unpin();
}

void HeapFilePage::set_dir_count(int32_t new_dir_count) {
  page.write_int32(0, new_dir_count);
}

void HeapFilePage::set_free_space(int32_t new_free_space) {
  page.write_int32(4, new_free_space);
}

void HeapFilePage::set_dir(int32_t idx, int32_t new_dir_value) {
  page.write_int32(8 + 4 * idx, new_dir_value);
}

int32_t HeapFilePage::get_dir_count() const {
  return page.read_int32(0);
}

int32_t HeapFilePage::get_free_space() const {
  return page.read_int32(4);
}

int32_t HeapFilePage::get_dir(int32_t idx) const {
  return page.read_int32(8 + 4 * idx);
}

bool HeapFilePage::get_record(int32_t dir_pos, Record& out) const {
  auto offset = get_dir(dir_pos);
  if (offset <= 0) {
    return false;
  }

  for (auto& v : out.values) {
    switch (v.datatype) {
    case DataType::INT: {
      v.value.as_int = page.read_int64(offset);
      offset += sizeof(int64_t);
      break;
    }
    case DataType::STR: {
      uint8_t len = page.read_uint8(offset);
      offset += 1;

      page.read(offset, len, v.value.as_str);
      offset += len;

      v.value.as_str[len] = '\0';
      break;
    }
    }
  }

  return true;
}

void HeapFilePage::delete_record(int32_t dir_pos) {
  set_dir(dir_pos, -1);
}

bool HeapFilePage::try_insert_record(const Record& record, RID* out_record_id) {
  int32_t needed_record_size = 0;
  for (size_t i = 0; i < record.values.size(); i++) {
    switch (record.values[i].datatype) {
    case DataType::INT: {
      needed_record_size += sizeof(int64_t);
      break;
    }
    case DataType::STR: {
      // one additional byte for the strlen at beginning
      needed_record_size += 1 + strlen(record.values[i].value.as_str);
      break;
    }
    }
  }

  int32_t dir_pos = 0;
  auto dir_count = get_dir_count();
  while (get_dir(dir_pos) > 0 && dir_pos < dir_count) {
    dir_pos++;
  }

  auto free_space = get_free_space();

  if (dir_pos < dir_count) { // found dir to reuse
    if (free_space < needed_record_size) {
      return false;
    }
    free_space -= needed_record_size;
  } else { // dir_pos == dir_count
    if (free_space < needed_record_size + 4) {
      return false;
    }
    dir_count++;
    set_dir_count(dir_count);
    free_space -= needed_record_size + 4;
  }
  set_free_space(free_space);

  int32_t offset = 8 + (dir_count * 4) + free_space;
  set_dir(dir_pos, offset);

  *out_record_id = RID(page.page_id.page_number, dir_pos);

  for (auto& v : record.values) {
    switch (v.datatype) {
    case DataType::INT: {
      page.write_int64(offset, v.value.as_int);
      offset += sizeof(int64_t);
      break;
    }
    case DataType::STR: {
      char* str = v.value.as_str;
      uint8_t len = strlen(str);
      page.write_int8(offset, len);
      offset += 1;

      page.write(offset, len, str);
      offset += len;
      break;
    }
    }
  }
  return true;
}

void HeapFilePage::edit_record(int32_t dir_pos, const Record& record) {
  int32_t offset = get_dir(dir_pos);
  for (auto& v : record.values) {
    switch (v.datatype) {
    case DataType::INT: {
      page.write_int64(offset, v.value.as_int);
      offset += sizeof(int64_t);
      break;
    }
    case DataType::STR: {
      throw std::runtime_error("Edit of strings nor supported");
      break;
    }
    }
  }
}

void HeapFilePage::vacuum(const Schema& schema) {
  char* page_buf = new char[Page::SIZE];

  int32_t dir_count = 0;
  int32_t free_space = Page::SIZE - 2 * sizeof(int32_t);
  auto dirs = reinterpret_cast<int32_t*>(page_buf + 2 * sizeof(int32_t));
  Record record_buf(schema);

  for (int32_t i = 0; i < get_dir_count(); i++) {
    if (get_dir(i) < 0) {
      continue;
    }
    get_record(i, record_buf);

    int32_t record_size = 0;
    for (size_t i = 0; i < record_buf.values.size(); i++) {
      switch (record_buf.values[i].datatype) {
      case DataType::INT: {
        record_size += sizeof(int64_t);
        break;
      }
      case DataType::STR: {
        // one additional byte for the strlen at beginning
        record_size += 1 + strlen(record_buf.values[i].value.as_str);
        break;
      }
      }
    }

    dir_count += 1;
    free_space -= record_size + sizeof(int32_t);

    auto offset = (2 + dir_count) * sizeof(int32_t) + free_space;
    dirs[dir_count - 1] = offset;
    page.read(get_dir(i), record_size, page_buf + offset);
  }

  page.write(0, Page::SIZE, page_buf);
  page.write_int32(0, dir_count);
  page.write_int32(4, free_space);
  delete[] page_buf;
}

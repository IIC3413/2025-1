#include "page.h"

#include <cstring>

#include "system/system.h"

void Page::read(size_t offset, size_t size, char* out) {
  assert(offset + size <= Page::SIZE);
  memcpy(out, bytes + offset, size);
}

uint8_t Page::read_uint8(size_t offset) {
  assert(offset + 1 <= Page::SIZE);
  return *reinterpret_cast<unsigned char*>(bytes + offset);
}

int32_t Page::read_int32(size_t offset) {
  assert(offset + 4 <= Page::SIZE);
  int32_t res;
  memcpy(reinterpret_cast<char*>(&res), bytes + offset, 4);

  return res;
}

int64_t Page::read_int64(size_t offset) {
  assert(offset + 8 <= Page::SIZE);
  int64_t res;
  memcpy(reinterpret_cast<char*>(&res), bytes + offset, 8);

  return res;
}

void Page::write(size_t offset, size_t size, char* in) {
  assert(offset + size <= Page::SIZE);

  log_mgr.update(page_id.file_id, page_id.page_number, offset, size, bytes + offset, in);

  memcpy(bytes + offset, in, size);
  dirty = true;
}

void Page::write_int8(size_t offset, uint8_t i) {
  assert(offset + 1 <= Page::SIZE);

  char* i_ptr = reinterpret_cast<char*>(&i);
  log_mgr.update(page_id.file_id, page_id.page_number, offset, 1, bytes + offset, i_ptr);

  bytes[offset] = *(i_ptr);
  dirty = true;
}

void Page::write_int32(size_t offset, int32_t i) {
  assert(offset + 4 <= Page::SIZE);

  char* i_ptr = reinterpret_cast<char*>(&i);
  log_mgr.update(page_id.file_id, page_id.page_number, offset, 4, bytes + offset, i_ptr);

  memcpy(bytes + offset, i_ptr, 4);
  dirty = true;
}

void Page::write_int64(size_t offset, int64_t i) {
  assert(offset + 8 <= Page::SIZE);

  char* i_ptr = reinterpret_cast<char*>(&i);
  log_mgr.update(page_id.file_id, page_id.page_number, offset, 8, bytes + offset, i_ptr);

  memcpy(bytes + offset, i_ptr, 8);
  dirty = true;
}

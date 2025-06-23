#pragma once

#include <atomic>
#include <cassert>

#include "storage/page_id.h"

class Page {
  friend class BufferManager;
  friend class FileManager;

public:
  static constexpr auto SIZE = 4096;

  // contains file_id and page_number of this page
  PageId page_id;

  // Read / Write interfaces
  void read(size_t offset, size_t size, char* out);
  uint8_t read_uint8(size_t offset);
  int32_t read_int32(size_t offset);
  int64_t read_int64(size_t offset);

  void write(size_t offset, size_t size, char* in);
  void write_int8(size_t offset, uint8_t);
  void write_int32(size_t offset, int32_t);
  void write_int64(size_t offset, int64_t);

  // get page number
  inline int32_t get_page_number() const noexcept {
    return page_id.page_number;
  };

  void pin() noexcept {
    pins++;
    second_chance = true;
  }

  void unpin() noexcept {
    assert(pins > 0 && "Cannot unpin if pin count is 0");
    pins--;
  }

private:
  // start memory address of the page, of size `Page::SIZE`
  char* bytes;

  // count of objects using this page, modified only by buffer_manager
  std::atomic<int32_t> pins;

  // used by the replacement policy
  bool second_chance;

  // true if data in memory is different from disk
  bool dirty;

  Page() noexcept
      : page_id(FileId(-1, FileId::UNASSIGNED), 0),
        bytes(nullptr),
        pins(0),
        second_chance(false),
        dirty(false) {}

  void set_bytes(char* bytes) noexcept {
    this->bytes = bytes;
  }

  void reassign(PageId page_id) noexcept {
    assert(!dirty && "Cannot reassign page if it is dirty");
    assert(pins == 0 && "Cannot reassign page if it is pinned");
    assert(second_chance == false && "Should not reassign page if second_chance is true");

    this->page_id = page_id;
    this->pins = 1;
    this->second_chance = true;
  }
};

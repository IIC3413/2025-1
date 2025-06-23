#include "buffer_manager.h"

#ifdef _MSC_VER
#include <malloc.h>
#else
#include <cstdlib>
#endif

#ifdef _MSC_VER
#define MDB_ALIGNED_ALLOC(ALIGNMENT, SIZE) _aligned_malloc(SIZE, ALIGNMENT)
#else
#define MDB_ALIGNED_ALLOC(ALIGNMENT, SIZE) std::aligned_alloc(ALIGNMENT, SIZE)
#endif

#ifdef _MSC_VER
#define MDB_ALIGNED_FREE _aligned_free
#else
#define MDB_ALIGNED_FREE free
#endif

#include <iostream>

#include "storage/page.h"
#include "system/system.h"

BufferManager::BufferManager(int64_t buffer_size)
    : frame_count(buffer_size / Page::SIZE),
      frames(new Page[frame_count]),
      data(reinterpret_cast<char*>(MDB_ALIGNED_ALLOC(Page::SIZE, frame_count * Page::SIZE))) {
  if (data == nullptr || frames == nullptr) {
    std::cerr << "ERROR: Could not allocate buffer, try using a smaller size\n";
    std::exit(EXIT_FAILURE);
  }

  for (int64_t i = 0; i < frame_count; i++) {
    frames[i].set_bytes(&data[i * Page::SIZE]);
  }

  page_map.reserve(frame_count);
}

BufferManager::~BufferManager() {
  flush();
  delete[] (frames);
  MDB_ALIGNED_FREE(data);
}

void BufferManager::flush() {
  // flush() is always called at destruction.
  // this is important to check to avoid segfault when program terminates before calling init()
  assert(frames != nullptr);
  for (int64_t i = 0; i < frame_count; i++) {
    assert(frames[i].pins == 0);
    if (frames[i].dirty) {
      file_mgr.flush(frames[i]);
    }
  }
}

void BufferManager::fake_flush() {
  // prevents a correct flush to test log manager recovery
  for (int64_t i = 0; i < frame_count; i++) {
    frames[i].dirty = false;
  }
}

Page& BufferManager::get_unused_page() {
  while (true) {
    if (frames[clock].pins == 0) {
      if (frames[clock].second_chance == false) {
        break;
      } else {
        frames[clock].second_chance = false;
      }
    }
    clock++;
    clock = clock < frame_count ? clock : 0;
  }
  return frames[clock];
}

Page& BufferManager::get_page(FileId file_id, int64_t page_number) {
  const PageId page_id(file_id, page_number);

  std::lock_guard<std::mutex> lck(pages_mutex);
  auto it = page_map.find(page_id);

  if (it == page_map.end()) {
    auto& page = get_unused_page();
    if (page.page_id.file_id.internal_id != FileId::UNASSIGNED) {
      page_map.erase(page.page_id);
    }

    if (page.dirty) {
      file_mgr.flush(page);
    }
    page.reassign(page_id);

    file_mgr.read_page(page_id, page.bytes);
    page_map.insert({page_id, &page});
    return page;
  } else { // page is the buffer
    (*it->second).pin();
    return *it->second;
  }
  // pages_mutex lock is released
}

Page& BufferManager::append_page(FileId file_id) {
  return get_page(file_id, file_mgr.count_pages(file_id));
}

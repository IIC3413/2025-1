#pragma once

#include <map>
#include <string>
#include <unistd.h>

#include "storage/file_id.h"
#include "storage/page.h"

class FileManager {
public:
  FileManager(const std::string& db_folder);

  ~FileManager() = default;

  // meant for being used when creating new disk structures
  FileId create_file_id(const std::string& filename);

  // meant for being used in catalog constructor
  FileId get_file_id(const std::string& filename, int internal_file_id);

  // meant for being used in recovery
  FileId get_file_id(int internal_file_id);

  // count how many pages a file have
  int64_t count_pages(FileId file_id) const {
    // We don't need mutex here as long as db is readonly
    return lseek(file_id.internal_id, 0, SEEK_END) / Page::SIZE;
  }

  inline const std::string get_file_path(const std::string& filename) const noexcept {
    return db_folder + "/" + filename;
  }

  // write page into disk
  void flush(Page& page_id) const;

  // read a page from disk into memory pointed by `bytes`.
  // `bytes` must point to the start memory position of `Page::SIZE` allocated bytes
  void read_page(PageId page_id, char* bytes) const;

private:
  // folder where all the used files will be
  const std::string db_folder;

  // internal -> fd
  std::map<int, int> internal_file_ids;
};

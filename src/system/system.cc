#include "system.h"

#include <cstdlib>
#include <iostream>

// memory for the global objects
static typename std::aligned_storage<sizeof(BufferManager), alignof(BufferManager)>::type buffer_mgr_buf;
static typename std::aligned_storage<sizeof(FileManager), alignof(FileManager)>::type file_mgr_buf;
static typename std::aligned_storage<sizeof(LogManager), alignof(LogManager)>::type log_mgr_buf;
static typename std::aligned_storage<sizeof(Catalog), alignof(Catalog)>::type catalog_buf;

BufferManager& buffer_mgr = reinterpret_cast<BufferManager&>(buffer_mgr_buf);
FileManager& file_mgr = reinterpret_cast<FileManager&>(file_mgr_buf);
LogManager& log_mgr = reinterpret_cast<LogManager&>(log_mgr_buf);
Catalog& catalog = reinterpret_cast<Catalog&>(catalog_buf);

System::System(const std::string& db_folder, int64_t buffer_size) {
  new (&file_mgr) FileManager(db_folder);
  new (&buffer_mgr) BufferManager(buffer_size);
  new (&log_mgr) LogManager();

  try {
    new (&catalog) Catalog("catalog.dat");
  } catch (...) {
    std::cerr << "Error reading catalog. Make sure the database was not created with a previous version."
              << std::endl;
    exit(EXIT_FAILURE);
  }
}

System System::init(const std::string& db_folder, int64_t buffer_size) {
  return System(db_folder, buffer_size);
}

System::~System() {
  log_mgr.~LogManager();
  catalog.~Catalog();
  buffer_mgr.~BufferManager();
  file_mgr.~FileManager();
}

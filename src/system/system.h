#pragma once

#include "system/buffer_manager.h"
#include "system/catalog.h"
#include "system/file_manager.h"
#include "system/log_manager.h"

class System {
public:
  ~System();

  static System init(const std::string& db_folder, int64_t buffer_size);

private:
  static inline bool initialized = false;

  System(const std::string& db_folder, int64_t buffer_size);
};

// global objects
extern FileManager& file_mgr;
extern BufferManager& buffer_mgr;
extern LogManager& log_mgr;
extern Catalog& catalog;

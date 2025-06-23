#include <iostream>

#include "system/system.h"
#include "system/log_helper.h"

using namespace LogHelper;

int main(int argc, char* argv[]) {
  std::ios_base::sync_with_stdio(false);

  if (argc < 2) {
    std::cerr << "Expected database folder as first argument" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  std::string db_directory = argv[1];

  // Need to call System::init before start using the database
  // When this object comes out of scope the database is no longer usable
  auto system = System::init(db_directory, BufferManager::DEFAULT_BUFFER_SIZE);
  auto log_entries = parse_log_entries();

  for (auto& log_entry : log_entries) {
    log_entry->print(std::cout);
  }
}

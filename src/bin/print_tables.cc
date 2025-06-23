#include <iostream>

#include "storage/heap_file/heap_file.h"
#include "system/system.h"

int main(int argc, char* argv[]) {
  std::ios_base::sync_with_stdio(false);

  if (argc < 2) {
    std::cout << "Usage: print_tables <db_directory>" << std::endl;
    return EXIT_FAILURE;
  }

  std::string db_directory(argv[1]);

  // Need to call System::init before start using the database
  // When this object comes out of scope the database is no longer usable
  auto system = System::init(db_directory, BufferManager::DEFAULT_BUFFER_SIZE);

  try {
    for (auto& table_info : catalog.get_tables()) {
      const Schema& schema = *table_info.schema;
      std::cout << table_info.name << "(";
      if (schema.columns.size() > 0) {
        std::cout << schema.columns[0].name;
        std::cout << ":" << (schema.columns[0].datatype == DataType::INT ? "INT" : "STR");
      }
      for (size_t i = 1; i < schema.columns.size(); i++) {
        std::cout << ',' << schema.columns[i].name;
        std::cout << ":" << (schema.columns[i].datatype == DataType::INT ? "INT" : "STR");
      }
      std::cout << ")\n";

      auto iter = table_info.heap_file->get_record_iter();

      Record record_buf(schema);
      iter->begin(record_buf);
      while (iter->next()) {
        std::cout << record_buf << '\n';
      }
      std::cout << '\n';
    }
  } catch (const std::exception& e) {
    std::cout << "Exception:\n";
    std::cout << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

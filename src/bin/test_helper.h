#include <iostream>

#include "system/system.h"

inline HeapFile& create_table(const std::string& table_name, std::vector<ColumnInfo>&& columns) {
  Schema table_schema(std::move(columns));
  Schema existing_table_schema;

  HeapFile* table = catalog.get_table(table_name, &existing_table_schema);
  if (table == nullptr) { // table doesn't exist
    table = catalog.create_table(table_name, table_schema);
  } else {
    std::cerr << "Database already has table " << table_name << std::endl;
    exit(EXIT_FAILURE);
  }
  return *table;
}

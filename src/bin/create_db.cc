#include <iostream>

#include "system/system.h"

constexpr int64_t GB = 1024 * 1024 * 1024; // 1 GB

HeapFile& get_or_create_table(const std::string& table_name, std::vector<ColumnInfo>&& columns) {
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

void populate_r() {
  for (int i = 0; i < 100; i++) {
    catalog.insert_record("R", {i, i + 1, "test.r" + std::to_string(i)});
  }
}

void populate_s() {
  for (int i = 0; i < 200; i++) {
    catalog.insert_record("S", {i, i * 2, "test.s" + std::to_string(i)});
  }
}

void populate_t() {
  for (int i = 0; i < 300; i++) {
    catalog.insert_record("T", {i, i * i, "test.t" + std::to_string(i)});
  }
}

void populate_u() {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      catalog.insert_record("U", {i, j, "test.u" + std::to_string(i) + "_" + std::to_string(j)});
    }
  }
}

void populate_v() {
  for (int i = 0; i < 50; i++) {
    for (int j = i; j < 50; j++) {
      catalog.insert_record("V", {i, j, "test.v" + std::to_string(i) + "_" + std::to_string(j)});
    }
  }
}

int main() {
  auto buffer_size = 1 * GB;
  std::string database_folder = "data/test_example";

  // Need to call System::init before start using the database
  // When this object comes out of scope the database is no longer usable
  auto system = System::init(database_folder, buffer_size);

  get_or_create_table("R", {{"r1", DataType::INT}, {"r2", DataType::INT}, {"r3", DataType::STR}});

  get_or_create_table("S", {{"s1", DataType::INT}, {"s2", DataType::INT}, {"s3", DataType::STR}});

  get_or_create_table("T", {{"t1", DataType::INT}, {"t2", DataType::INT}, {"t3", DataType::STR}});

  get_or_create_table("U", {{"u1", DataType::INT}, {"u2", DataType::INT}, {"u3", DataType::STR}});

  get_or_create_table("V", {{"v1", DataType::INT}, {"v2", DataType::INT}, {"v3", DataType::STR}});

  populate_r();
  populate_s();
  populate_t();
  populate_u();
  populate_v();

  std::cout << "Database " << database_folder << " created" << std::endl;

  return EXIT_SUCCESS;
}

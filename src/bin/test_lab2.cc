#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#include "system/system.h"

constexpr int64_t GB = 1024 * 1024 * 1024; // 1 GB

std::vector<int64_t> shuffle_numbers(int64_t N) {
  std::vector<int64_t> numbers(N);
  for (int i = 0; i < N; ++i) {
    numbers[i] = i;
  }

  unsigned seed = 314;
  std::shuffle(numbers.begin(), numbers.end(), std::default_random_engine(seed));
  return numbers;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cout << "Expecting 1 parameter, received " << (argc - 1) << "\n";
    return EXIT_FAILURE;
  }

  int64_t t = atol(argv[1]);
  if (t <= 0) {
    std::cout << "Expect positive integer as parameter\n";
    return EXIT_FAILURE;
  }

  std::cout << "test " << t << "\n";

  auto buffer_size = 1 * GB;
  std::string database_folder = "data/test_example";

  // Need to call System::init before start using the database
  // When this object comes out of scope the database is no longer usable
  auto system = System::init(database_folder, buffer_size);

  Schema table1_schema({{"col1", DataType::STR}, {"col2", DataType::INT}});

  Schema existing_table_schema;

  std::string table1 = "test_1";
  HeapFile* table = catalog.get_table(table1, &existing_table_schema);

  if (table == nullptr) { // table doesn't exist
    table = catalog.create_table(table1, table1_schema);
    catalog.create_index(table1, 1); // 1 represents second column (col2)
    auto index = catalog.get_index(table1);
    assert(index != nullptr);

    auto numbers = shuffle_numbers(t);
    int count = 0;
    for (auto i : numbers) {
      catalog.insert_record(table1, {"test_record_" + std::to_string(count++), i});
    }

    auto iter = index->get_iter(Value(int64_t(0)), Value(99999999));
    // we call Value(int64_t(0)) instead of Value(0) because c++ may interpret 0 as
    // nullptr and be ambiguous with the constructor Value(const char*)

    Record& record_buf = catalog.get_record_buf(table1);
    iter->begin(record_buf);
    int i_count = 0;
    while (iter->next()) {
      if (i_count != record_buf.values[1].value.as_int) {
        std::cout << "error at t: " << t << "\n";
        std::cout << "got: " << record_buf.values[1].value.as_int << "\n";
        std::cout << "expected: " << i_count << "\n";
        std::cout << record_buf << "\n";
        return 1;
      }
      i_count++;
    }

    if (i_count != t) {
      std::cout << "error at t: " << t << "\n";
      std::cout << "finished early\n";
      std::cout << "terminated at: " << i_count << "\n";
      return 1;
    }
  } else {
    std::cout << "Test did not run, delete old database folder\n";
    return EXIT_FAILURE;
  }

  std::cout << "Test passed!\n";
  return EXIT_SUCCESS;
}

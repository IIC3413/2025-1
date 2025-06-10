#pragma once

#include <cstddef>
#include <memory>
#include <string>

#include "relational_model/index.h"

using TableId = size_t;

class Schema;
class HeapFile;
class Record;

struct TableInfo {
  std::string name;
  std::unique_ptr<Schema> schema;
  std::unique_ptr<HeapFile> heap_file;

  // used as buffer, to avoid allocations
  std::unique_ptr<Record> record_buf;

  // nullptr if there is not index
  std::unique_ptr<Index> index;

  uint64_t cardinality;

  TableInfo(
      const std::string& name,
      std::unique_ptr<Schema> _schema,
      std::unique_ptr<HeapFile> heap_file,
      std::unique_ptr<Index> index,
      uint64_t cardinality
  );
};

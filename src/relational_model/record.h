#pragma once

#include <cstdint>
#include <ostream>
#include <variant>
#include <vector>

#include "relational_model/schema.h"
#include "relational_model/value.h"

class Record {
public:
  Record(const Schema& schema);

  Record(std::vector<DataType> types);

  Record(const Record& other) = delete;

  Record(Record&& other);

  Record(std::vector<Value>&& other);

  void set(const std::vector<std::variant<std::string_view, int64_t>>& values);

  void set(const std::vector<Value>& values);

  friend std::ostream& operator<<(std::ostream& os, const Record& o) {
    char separator[2] = {'\0', '\0'};
    for (unsigned i = 0; i < o.values.size(); i++) {
      os << separator;
      os << o.values[i];
      separator[0] = ',';
    }
    return os;
  }

  bool operator==(const Record& other) const {
    return this->values == other.values;
  }

  uint64_t hash() {
    Hasher hasher;
    return hasher.operator()(*this);
  }

  std::vector<Value> values;

  struct Hasher {
    uint64_t operator()(const Record& record) const {
      uint64_t res = 0;
      for (const auto& value: record.values) {
        res ^= value.get_hash();
      }
      return res;
    }
  };

};

class RecordRef {
public:
  RecordRef(uint_fast32_t size) {
    values.resize(size);
  }

  RecordRef(const RecordRef& other) = delete;

  friend std::ostream& operator<<(std::ostream& os, const RecordRef& o) {
    char separator[2] = {'\0', '\0'};
    for (unsigned i = 0; i < o.values.size(); i++) {
      os << separator;
      os << *o.values[i];
      separator[0] = ',';
    }
    return os;
  }

  std::vector<const Value*> values;
};

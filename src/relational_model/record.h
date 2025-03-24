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

  Record(const Record& other) = delete;

  void set(const std::vector<std::variant<std::string_view, int64_t>>& values);

  friend std::ostream& operator<<(std::ostream& os, const Record& o) {
    char separator[2] = {'\0', '\0'};
    for (unsigned i = 0; i < o.values.size(); i++) {
      os << separator;
      os << o.values[i];
      separator[0] = ',';
    }
    return os;
  }

  std::vector<Value> values;
};

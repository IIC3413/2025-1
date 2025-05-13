#include "record.h"

#include <cassert>
#include <cstring>

Record::Record(const Schema& schema) {
  for (const auto& col : schema.columns) {
    switch (col.datatype) {
    case DataType::INT: {
      values.push_back(Value((int64_t)0));
      break;
    }
    case DataType::STR: {
      values.push_back(Value(""));
      break;
    }
    }
  }
}

void Record::set(const std::vector<std::variant<std::string_view, int64_t>>& new_values) {
  assert(new_values.size() == values.size());

  for (size_t i = 0; i < values.size(); i++) {
    auto& value = new_values[i];

    switch (values[i].datatype) {
    case DataType::INT: {
      assert(std::holds_alternative<int64_t>(value));
      values[i].value.as_int = std::get<int64_t>(value);
      break;
    }
    case DataType::STR: {
      assert(std::holds_alternative<std::string_view>(value));
      auto& str = std::get<std::string_view>(value);
      assert(str.size() <= Value::MAX_STRLEN);
      memcpy(values[i].value.as_str, str.data(), str.size() + 1);
      break;
    }
    }
  }
}

void Record::set(const std::vector<Value>& new_values) {
  assert(new_values.size() == values.size());
  for (size_t i = 0; i < values.size(); i++) {
    values[i] = Value(new_values[i]);
  }
}

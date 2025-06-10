#pragma once

#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "relational_model/record.h"
#include "relational_model/schema.h"
#include "storage/file_id.h"
#include "storage/heap_file/rid.h"
#include "storage/heap_file/heap_file.h"

class Catalog {
public:
  Catalog(const std::string& filename);

  ~Catalog();

  // may return nullptr if table does not exist
  // sets the schema when the table is found
  HeapFile* get_table(const std::string& table_name, Schema* schema);

  HeapFile* create_table(const std::string& table_name, const Schema&);

  bool table_exists(const std::string& table_name) const;

  DataType get_datatype(const std::string& table_name, const std::string& col_name) const;

  RID insert_record(
      const std::string& table_name, const std::vector<std::variant<std::string_view, int64_t>>& values
  );

  void delete_record(const std::string& table_name, RID rid);

  Record& get_record_buf(const std::string& table_name);

  const TableInfo& get_table_info(const std::string& table_name) const;

  FileId get_file_id(TableId tid);

  void create_index(const std::string& table_name, int key_col_idx);

  Index* get_index(const std::string& table_name);

  int64_t get_table_cardinality(const std::string& table_name) const;

private:
  std::map<std::string, int64_t> table_name_idx;

  std::vector<TableInfo> tables;

  std::fstream file;

  static std::string normalize(const std::string& table_name);

  int64_t read_int64();

  std::string read_string();

  int64_t get_table_pos(const std::string& table_name) const;

  void write_int64(const int64_t);

  void write_string(const std::string&);
};

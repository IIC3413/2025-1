#include "catalog.h"

#include <algorithm>
#include <stdexcept>

#include "exceptions/exceptions.h"
#include "relational_model/schema.h"
#include "storage/b_plus_tree/b_plus_tree.h"
#include "storage/heap_file/heap_file.h"
#include "system/system.h"

using namespace std;

std::string Catalog::normalize(const std::string& table_name) {
  std::string res = table_name;
  std::transform(res.begin(), res.end(), res.begin(), [](unsigned char c) { return std::tolower(c); });

  for (char c : res) {
    if (c < 'a' && c > 'z' && c != '_') {
      throw QueryException(
          "wrong table name: `" + table_name + "`. Only a-z letters and underscore ('_') are allowed."
      );
    }
  }
  return res;
}

int64_t Catalog::get_table_pos(const std::string& table_name) const {
  std::string normalized_table_name = normalize(table_name);
  auto found = table_name_idx.find(normalized_table_name);
  if (found != table_name_idx.end()) {
    return found->second;
  } else {
    throw QueryException("table: `" + table_name + "` does not exist.");
  }
}

Catalog::Catalog(const string& filename) {
  auto file_path = file_mgr.get_file_path(filename);
  file.open(file_path, ios::out | ios::app);
  if (file.fail()) {
    throw std::runtime_error("Could not open file " + filename);
  }
  file.close();
  file.open(file_path, ios::in | ios::out | ios::binary);

  file.seekg(0, file.end);
  if (file.tellg() == 0) {
    return; // catalog file is new
  }

  file.seekg(0, file.beg);

  int64_t tables_count = read_int64();
  for (int64_t i = 0; i < tables_count; ++i) {
    std::vector<ColumnInfo> columns;

    std::string table_name = read_string();
    int64_t table_cardinality = read_int64();
    for (int64_t c = 0; c < table_cardinality; ++c) {
      DataType d = static_cast<DataType>(read_int64());
      std::string col_name = read_string();
      columns.push_back({col_name, d});
    }

    auto schema = std::make_unique<Schema>(std::move(columns));

    auto& schema_ref = *schema.get();
    auto heap_file = std::make_unique<HeapFile>(i, schema_ref, table_name);
    table_name_idx.insert({table_name, tables.size()});

    std::unique_ptr<Index> index;
    IndexType index_type = static_cast<IndexType>(read_int64());
    switch (index_type) {
    case IndexType::B_PLUS_TREE: {
      auto key_col_idx = read_int64();
      index = std::make_unique<BPlusTree>(*heap_file.get(), key_col_idx, normalize(table_name) + ".bpt");
      break;
    }
    case IndexType::NONE:
      break;
    }

    tables.emplace_back(table_name, std::move(schema), std::move(heap_file), std::move(index));
  }
}

Catalog::~Catalog() {
  file.seekg(0, file.beg);

  write_int64(tables.size());
  for (auto& table_info : tables) {
    write_string(table_info.name);
    auto& schema = table_info.schema;

    write_int64(schema->columns.size());
    for (size_t i = 0; i < schema->columns.size(); i++) {
      write_int64(static_cast<int64_t>(schema->columns[i].datatype));
      write_string(schema->columns[i].name);
    }

    // write index type
    if (table_info.index == nullptr) {
      write_int64(static_cast<uint64_t>(IndexType::NONE));
    } else {
      auto index_type = table_info.index->get_type();
      write_int64(static_cast<uint64_t>(index_type));
      switch (index_type) {
      case IndexType::B_PLUS_TREE: {
        auto casted = reinterpret_cast<BPlusTree*>(table_info.index.get());
        write_int64(casted->key_column_idx);
        break;
      }
      case IndexType::NONE:
        break;
      }
    }
  }

  file.close();
}

int64_t Catalog::read_int64() {
  int64_t res = 0;
  uint8_t buf[8];
  file.read((char*)buf, sizeof(buf));

  for (int i = 0, shift = 0; i < 8; ++i, shift += 8) {
    res |= static_cast<int64_t>(buf[i]) << shift;
  }

  if (!file.good()) {
    throw std::runtime_error("Error reading int64");
  }

  return res;
}

string Catalog::read_string() {
  auto len = read_int64();
  char* buf = new char[len];
  file.read(buf, len);
  string res(buf, len);
  delete[] buf;
  return res;
}

void Catalog::write_int64(const int64_t n) {
  uint8_t buf[8];
  for (unsigned int i = 0, shift = 0; i < sizeof(buf); ++i, shift += 8) {
    buf[i] = (n >> shift) & 0xFF;
  }
  file.write(reinterpret_cast<const char*>(buf), sizeof(buf));
}

void Catalog::write_string(const string& s) {
  write_int64(s.size());
  file.write(s.c_str(), s.size());
}

HeapFile* Catalog::create_table(const std::string& table_name, const Schema& schema) {
  std::string normalized_table_name = normalize(table_name);

  auto found = table_name_idx.find(normalized_table_name);

  if (found != table_name_idx.end()) {
    throw QueryException("table: `" + table_name + "` already exists.");
  }

  TableId table_id = tables.size();
  table_name_idx.insert({normalized_table_name, table_id});

  auto heap_file = std::make_unique<HeapFile>(table_id, schema, normalized_table_name);

  tables.emplace_back(normalized_table_name, std::make_unique<Schema>(schema), std::move(heap_file), nullptr);

  return tables.back().heap_file.get();
}

HeapFile* Catalog::get_table(const std::string& table_name, Schema* schema) {
  std::string normalized_table_name = normalize(table_name);

  auto found = table_name_idx.find(normalized_table_name);

  if (found != table_name_idx.end()) {
    *schema = *tables[found->second].schema;
    return tables[found->second].heap_file.get();
  } else {
    return nullptr;
  }
}

RID Catalog::insert_record(
    const std::string& table_name, const std::vector<std::variant<std::string_view, int64_t>>& values
) {
  auto table_pos = get_table_pos(table_name);

  auto& record = *tables[table_pos].record_buf;
  record.set(values);

  auto rid = tables[table_pos].heap_file->insert_record(record);

  auto index = tables[get_table_pos(table_name)].index.get();
  if (index != nullptr) {
    index->insert_record(rid);
  }

  return rid;
}

void Catalog::delete_record(const std::string& table_name, RID rid) {
  auto table_pos = get_table_pos(table_name);

  // MUST delete from the index before the table, otherwise rid will be invalid
  auto index = get_index(table_name);
  if (index != nullptr) {
    index->delete_record(rid);
  }
  tables[table_pos].heap_file->delete_record(rid);
}

Record& Catalog::get_record_buf(const std::string& table_name) {
  return *tables[get_table_pos(table_name)].record_buf;
}

bool Catalog::table_exists(const std::string& table_name) const {
  std::string normalized_table_name = normalize(table_name);
  auto found = table_name_idx.find(normalized_table_name);
  return found != table_name_idx.end();
}

DataType Catalog::get_datatype(const std::string& table_name, const std::string& col_name) const {
  std::string normalized_table_name = normalize(table_name);
  auto found = table_name_idx.find(normalized_table_name);
  if (found == table_name_idx.end())
    throw QueryException("Table `" + table_name + "` does not exist");

  const auto& schema = tables[found->second].schema;

  for (size_t i = 0; i < schema->columns.size(); i++) {
    if (schema->columns[i].name == col_name) {
      return schema->columns[i].datatype;
    }
  }

  throw QueryException("Column `" + col_name + "` does not exist in table `" + table_name + "`");
}

const TableInfo& Catalog::get_table_info(const std::string& table_name) const {
  std::string normalized_table_name = normalize(table_name);
  return tables[get_table_pos(table_name)];
}

FileId Catalog::get_file_id(TableId tid) {
  assert(tables.size() > tid);
  return tables[tid].heap_file->file_id;
}

void Catalog::create_index(const std::string& table_name, int key_col_idx) {
  auto table_pos = get_table_pos(table_name);

  auto& table_info = tables[table_pos];
  if (table_info.index != nullptr) {
    throw QueryException("table: `" + table_name + "` already has an index.");
  }

  table_info.index =
      std::make_unique<BPlusTree>(*table_info.heap_file, key_col_idx, normalize(table_name) + ".bpt");

  auto iter = table_info.heap_file->get_record_iter();
  Record record_buf(*table_info.schema);
  iter->begin(record_buf);
  while (iter->next()) {
    table_info.index->insert_record(iter->get_current_RID());
  }
}

Index* Catalog::get_index(const std::string& table_name) {
  return tables[get_table_pos(table_name)].index.get();
}

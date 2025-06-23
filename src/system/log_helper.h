#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "system/log_manager.h"
#include "system/system.h"

namespace LogHelper {
inline int32_t read_int32(std::fstream& log_file) {
  int32_t res;
  log_file.read((char*)&res, 4);
  return res;
}

inline uint8_t read_uint8(std::fstream& log_file) {
  uint8_t res;
  log_file.read((char*)&res, 1);
  return res;
}

class LogEntry {
public:
  int32_t lsn;

  LogEntry(int32_t lsn)
      : lsn(lsn) {}

  virtual ~LogEntry() = default;

  virtual LogType get_type() const = 0;

  virtual void print(std::ostream& os) const = 0;
};

class StartEntry : public LogEntry {
public:
  int32_t tid;

  StartEntry(int32_t lsn, int32_t tid)
      : LogEntry(lsn),
        tid(tid) {}

  LogType get_type() const override {
    return LogType::START;
  }

  void print(std::ostream& os) const override {
    os << "<" << lsn << ",START," << tid << ">\n";
  }
};

class CommitEntry : public LogEntry {
public:
  int32_t tid;

  CommitEntry(int32_t lsn, int32_t tid)
      : LogEntry(lsn),
        tid(tid) {}

  LogType get_type() const override {
    return LogType::COMMIT;
  }

  void print(std::ostream& os) const override {
    os << "<" << lsn << ",COMMIT," << tid << ">\n";
  }
};

class UpdateEntry : public LogEntry {
public:
  int32_t tid;
  int32_t prev_lsn;
  int32_t file_id;
  int32_t page_number;
  int32_t offset;
  int32_t len;

  std::string old_bytes;
  std::string new_bytes;

  UpdateEntry(
      int32_t lsn,
      int32_t tid,
      int32_t prev_lsn,
      int32_t file_id,
      int32_t page_number,
      int32_t offset,
      int32_t len,
      std::string old_bytes,
      std::string new_bytes
  )
      : LogEntry(lsn),
        tid(tid),
        prev_lsn(prev_lsn),
        file_id(file_id),
        page_number(page_number),
        offset(offset),
        len(len),
        old_bytes(std::move(old_bytes)),
        new_bytes(std::move(new_bytes)) {}

  LogType get_type() const override {
    return LogType::UPDATE;
  }

  void print(std::ostream& os) const override {
    os << "<" << lsn << ",UPDATE," << tid << ',' << prev_lsn << ',' << file_id << ',' << page_number << ','
       << offset << ',' << len << ',';
    os << "0x";
    os << std::hex;
    for (int i = 0; i < len; i++) {
      std::cout << std::setw(2) << std::setfill('0') << (int)static_cast<uint8_t>(old_bytes.data()[i]);
    }
    os << ',';
    os << "0x";
    for (int i = 0; i < len; i++) {
      os << std::setw(2) << std::setfill('0') << (int)static_cast<uint8_t>(old_bytes.data()[i]);
    }
    os << std::dec << ">\n";
  }
};

class CheckpointEntry : public LogEntry {
public:
  std::vector<int32_t> tx_ids;

  CheckpointEntry(int32_t lsn, std::vector<int32_t> tx_ids)
      : LogEntry(lsn),
        tx_ids(std::move(tx_ids)) {}

  LogType get_type() const override {
    return LogType::CHKP;
  }

  void print(std::ostream& os) const override {
    os << "<" << lsn << ",CHKP," << tx_ids.size();
    for (size_t i = 0; i < tx_ids.size(); i++) {
      os << "," << tx_ids[i];
    }
    os << ">\n";
  }
};

inline std::vector<std::unique_ptr<LogEntry>> parse_log_entries() {
  auto log_path = file_mgr.get_file_path("IIC3413.log");
  std::fstream log_file(log_path, std::ios::binary | std::ios::in);

  if (log_file.fail()) {
    std::cerr << "Could not open the log at path: " << log_path << "\n";
    std::exit(EXIT_FAILURE);
  }

  char* buffer = new char[Page::SIZE];

  std::vector<std::unique_ptr<LogEntry>> log_entries;

  while (log_file.good()) {
    auto lsn = read_int32(log_file);

    if (log_file.eof()) {
        break;
    }

    auto log_type = static_cast<LogType>(read_uint8(log_file));

    switch (log_type) {
    case LogType::START: {
      auto tid = read_int32(log_file);
      log_entries.push_back(std::make_unique<StartEntry>(lsn, tid));
      break;
    }
    case LogType::COMMIT: {
      auto tid = read_int32(log_file);
      log_entries.push_back(std::make_unique<CommitEntry>(lsn, tid));
      break;
    }
    case LogType::UPDATE: {
      auto tid = read_int32(log_file);
      auto prev_lsn = read_int32(log_file);
      auto file_id = read_int32(log_file);
      auto page_number = read_int32(log_file);
      auto offset = read_int32(log_file);
      auto len = read_int32(log_file);

      log_file.read(buffer, len);
      std::string old_bytes(buffer, len);

      log_file.read(buffer, len);
      std::string new_bytes(buffer, len);

      log_entries.push_back(std::make_unique<UpdateEntry>(
          lsn, tid, prev_lsn, file_id, page_number, offset, len, old_bytes, new_bytes
      ));
      break;
    }
    case LogType::CHKP: {
      std::vector<int32_t> tx_ids;

      auto n = read_int32(log_file);
      for (int i = 0; i < n; i++) {
        auto tid = read_int32(log_file);
        tx_ids.push_back(tid);
      }

      log_entries.push_back(std::make_unique<CheckpointEntry>(lsn, std::move(tx_ids)));
      break;
    }
    }
  }
  delete[] buffer;

  return log_entries;
}
} // namespace LogHelper

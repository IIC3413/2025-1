#pragma once

#include <fstream>
#include <map>
#include <mutex>
#include <vector>

#include "storage/file_id.h"

using TxId = uint32_t;

enum class LogType {
  START = 0,
  COMMIT = 1,
  UPDATE = 2,
  CHKP = 3,
};

class LogManager {
public:
  static inline thread_local TxId tx_id = 0;

  static constexpr int WRITE_MODE_UNDEFINED = 0;
  static constexpr int WRITE_MODE_U = 1;
  static constexpr int WRITE_MODE_UR = 2;

  LogManager();

  ~LogManager();

  void start();

  void commit();

  void update(
      FileId file_id,
      uint32_t page_num,
      uint32_t offset,
      uint32_t len,
      const char* old_bytes,
      const char* new_bytes
  );

  void chkp(const std::vector<TxId>& tids);

  TxId get_new_tid();

  void clear_log();

private:
  std::mutex log_mutex;

  std::fstream log_file;

  char* buffer;

  TxId tx_counter = 0;

  // only get or modify this number if log_mutex is locked
  int32_t current_lsn = 0;

  std::map<TxId, int32_t> tid_to_last_lsn;

  // only call this if log_mutex is locked
  int32_t get_lsn() {
    return current_lsn++;
  }
};

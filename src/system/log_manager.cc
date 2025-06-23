#include "log_manager.h"

#include "system/system.h"

LogManager::LogManager() {
  // buffer size must be big enough to handle a write of an entire page
  buffer = new char[3 * Page::SIZE];

  auto log_path = file_mgr.get_file_path("IIC3413.log");
  log_file.open(log_path, std::ios::out | std::ios::app);
}

LogManager::~LogManager() {
  delete[] buffer;
}

TxId LogManager::get_new_tid() {
  std::lock_guard<std::mutex> lock(log_mutex);
  auto res = tx_counter++;
  return res;
}

void LogManager::clear_log() {
  log_file.close();

  auto log_path = file_mgr.get_file_path("IIC3413.log");
  log_file.open(log_path, std::ios::out | std::ios::trunc);
}

void write_int32(int32_t i, char* out) {
  char* i_ptr = reinterpret_cast<char*>(&i);

  out[0] = *(i_ptr++);
  out[1] = *(i_ptr++);
  out[2] = *(i_ptr++);
  out[3] = *(i_ptr++);
}

void LogManager::start() {
  std::lock_guard<std::mutex> lock(log_mutex);

  auto lsn = get_lsn();
  tid_to_last_lsn[tx_id] = lsn;

  write_int32(lsn, &buffer[0]);
  buffer[4] = static_cast<unsigned char>(LogType::START);
  write_int32(tx_id, &buffer[5]);

  log_file.write(buffer, 9);
}

void LogManager::commit() {
  std::lock_guard<std::mutex> lock(log_mutex);

  auto lsn = get_lsn();
  tid_to_last_lsn.erase(tx_id);

  write_int32(lsn, &buffer[0]);
  buffer[4] = static_cast<unsigned char>(LogType::COMMIT);
  write_int32(tx_id, &buffer[5]);

  log_file.write(buffer, 9);
  log_file.flush();
}

void LogManager::chkp(const std::vector<TxId>& tids) {
  std::lock_guard<std::mutex> lock(log_mutex);

  auto lsn = get_lsn();

  write_int32(lsn, &buffer[0]);
  buffer[4] = static_cast<unsigned char>(LogType::CHKP);
  write_int32(tids.size(), &buffer[5]);

  for (size_t i = 0; i < tids.size(); i++) {
    tid_to_last_lsn.erase(tx_id);
    write_int32(tids[i], &buffer[9 + (i * 4)]);
  }
  log_file.write(buffer, 9 + (4 * tids.size()));
  log_file.flush();
}

void LogManager::update(
    FileId file_id,
    uint32_t page_num,
    uint32_t offset,
    uint32_t len,
    const char* old_bytes,
    const char* new_bytes
) {
  std::lock_guard<std::mutex> lock(log_mutex);

  auto lsn = get_lsn();
  auto prevLSN = tid_to_last_lsn[tx_id];
  tid_to_last_lsn[tx_id] = lsn;

  write_int32(lsn, &buffer[0]);
  buffer[4] = static_cast<unsigned char>(LogType::UPDATE);
  char* current_write_ptr = &buffer[5];

  write_int32(tx_id, current_write_ptr);
  current_write_ptr += 4;

  write_int32(prevLSN, current_write_ptr);
  current_write_ptr += 4;

  write_int32(file_id.internal_id, current_write_ptr);
  current_write_ptr += 4;

  write_int32(page_num, current_write_ptr);
  current_write_ptr += 4;

  write_int32(offset, current_write_ptr);
  current_write_ptr += 4;

  write_int32(len, current_write_ptr);
  current_write_ptr += 4;

  memcpy(current_write_ptr, old_bytes, len);
  current_write_ptr += len;

  memcpy(current_write_ptr, new_bytes, len);
  current_write_ptr += len;

  size_t total_written = current_write_ptr - buffer;
  log_file.write(buffer, total_written);
}

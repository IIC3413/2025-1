#include <thread>

#include "bin/test_helper.h"
#include "system/system.h"

void transaction1() {
  log_mgr.tx_id = 1;
  log_mgr.start();

  catalog.edit_record("R", RID(0, 0), {111, 101});
  catalog.edit_record("S", RID(0, 0), {111, 101});
}

void transaction2() {
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  log_mgr.tx_id = 2;
  log_mgr.start();

  catalog.edit_record("R", RID(0, 0), {222, 202});
  catalog.edit_record("S", RID(0, 1), {222, 202});
}

void transaction3() {
  std::this_thread::sleep_for(std::chrono::milliseconds(200));
  log_mgr.tx_id = 3;
  log_mgr.start();

  catalog.edit_record("R", RID(0, 0), {333, 303});
  catalog.edit_record("S", RID(0, 2), {333, 303});
}

int main() {
  std::string database_folder = "data/tests/t2";
  {
    auto system = System::init(database_folder, BufferManager::DEFAULT_BUFFER_SIZE);

    create_table("R", {{"r1", DataType::INT}, {"r2", DataType::INT}});
    create_table("S", {{"s1", DataType::INT}, {"s2", DataType::INT}});

    // initial populate
    for (int i = 0; i < 10; i++) {
      catalog.insert_record("R", {i, 2 * i});
    }
    for (int i = 0; i < 20; i++) {
      catalog.insert_record("S", {i, i * i});
    }
    log_mgr.clear_log();
  }

  {
    auto system = System::init(database_folder, BufferManager::DEFAULT_BUFFER_SIZE);

    std::thread t1(transaction1);
    std::thread t2(transaction2);
    std::thread t3(transaction3);

    t1.join();
    t2.join();
    t3.join();
  }

  return 0;
}

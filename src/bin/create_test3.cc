#include <thread>

#include "bin/test_helper.h"
#include "system/system.h"

// T1       T2       T3       T4
// Start
// Write(x)
//          Start
//          Write(x)
//          Write(y)
//          Commit
// Write(y)
// Commit
//                   Start
//                   Write(x)
//                            Start
//                            Write(z)
//                            Write(x)
//                   Write(z)

// x = "R", RID(0, 1)
// y = "S", RID(0, 2)
// z = "S", RID(0, 5)

void transaction1() {
  log_mgr.tx_id = 1;
  log_mgr.start();
  catalog.edit_record("R", RID(0, 1), {111});

  std::this_thread::sleep_for(std::chrono::milliseconds(200));

  catalog.edit_record("S", RID(0, 2), {11});
  log_mgr.commit();
}

void transaction2() {
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  log_mgr.tx_id = 2;
  log_mgr.start();

  catalog.edit_record("S", RID(0, 2), {222});
  log_mgr.commit();
}

void transaction3() {
  std::this_thread::sleep_for(std::chrono::milliseconds(300));
  log_mgr.tx_id = 3;
  log_mgr.start();
  catalog.edit_record("R", RID(0, 1), {333});

  std::this_thread::sleep_for(std::chrono::milliseconds(200));

  catalog.edit_record("S", RID(0, 5), {53});
}

void transaction4() {
  std::this_thread::sleep_for(std::chrono::milliseconds(400));
  log_mgr.tx_id = 4;
  log_mgr.start();
  catalog.edit_record("S", RID(0, 5), {54});
  catalog.edit_record("R", RID(0, 1), {444});
}

int main() {
  std::string database_folder = "data/tests/t3";
  {
    auto system = System::init(database_folder, BufferManager::DEFAULT_BUFFER_SIZE);

    create_table("R", {{"r1", DataType::INT}});
    create_table("S", {{"s1", DataType::INT}});

    // initial populate
    for (int i = 0; i < 10; i++) {
      catalog.insert_record("R", {i});
    }
    for (int i = 0; i < 20; i++) {
      catalog.insert_record("S", {i});
    }

    log_mgr.clear_log();
  }

  {
    auto system = System::init(database_folder, BufferManager::DEFAULT_BUFFER_SIZE);

    std::thread t1(transaction1);
    std::thread t2(transaction2);
    std::thread t3(transaction3);
    std::thread t4(transaction4);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
  }

  return 0;
}

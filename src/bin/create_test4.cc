#include <thread>

#include "bin/test_helper.h"
#include "system/system.h"

//    | T1       T2       T3       T4       T5
//  0 | Start
//    | Write(a)
//  1 |          Start
//    |          Write(b)
//  2 | Commit
//  3 |                   Start
//  4 |          Write(c)
//  5 |                   Write(a)
//  6 |          Commit
//  7 | ---------------- CHKP T2 T3 ----------------
//  8 |                            Start
//    |                            Write(b)
//    |                            Write(b)
//  9 |                                     Start
// 10 |                            Write(b)
// 11 |                                     Write(c)
// 12 |                            Commit
// 13 |                   Write(a)
// 14 |                                     Write(b)

// a = "R", RID(0, 1)
// b = "S", RID(0, 2)
// c = "S", RID(0, 5)

void transaction1() {
  log_mgr.tx_id = 1;
  log_mgr.start();
  catalog.edit_record("R", RID(0, 1), {101});

  std::this_thread::sleep_for(std::chrono::milliseconds(200));

  log_mgr.commit();
}

void transaction2() {
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  log_mgr.tx_id = 2;
  log_mgr.start();
  catalog.edit_record("S", RID(0, 2), {201});

  std::this_thread::sleep_for(std::chrono::milliseconds(300));

  catalog.edit_record("S", RID(0, 5), {201});

  std::this_thread::sleep_for(std::chrono::milliseconds(200));

  log_mgr.commit();
}

void transaction3() {
  std::this_thread::sleep_for(std::chrono::milliseconds(300));
  log_mgr.tx_id = 3;
  log_mgr.start();

  std::this_thread::sleep_for(std::chrono::milliseconds(200));

  catalog.edit_record("R", RID(0, 1), {301});

  std::this_thread::sleep_for(std::chrono::milliseconds(800));

  catalog.edit_record("R", RID(0, 1), {302});
}

void transaction4() {
  std::this_thread::sleep_for(std::chrono::milliseconds(800));
  log_mgr.tx_id = 4;
  log_mgr.start();
  catalog.edit_record("S", RID(0, 2), {401});
  catalog.edit_record("S", RID(0, 2), {402});
  std::this_thread::sleep_for(std::chrono::milliseconds(200));
  catalog.edit_record("S", RID(0, 2), {403});
  std::this_thread::sleep_for(std::chrono::milliseconds(200));
  log_mgr.commit();
}

void transaction5() {
  std::this_thread::sleep_for(std::chrono::milliseconds(900));
  log_mgr.tx_id = 5;
  log_mgr.start();

  std::this_thread::sleep_for(std::chrono::milliseconds(200));
  catalog.edit_record("S", RID(0, 5), {401});
  std::this_thread::sleep_for(std::chrono::milliseconds(300));
  catalog.edit_record("S", RID(0, 2), {404});
}

int main() {
  std::string database_folder = "data/tests/t4";
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
    std::thread t5(transaction5);

    std::this_thread::sleep_for(std::chrono::milliseconds(700));
    buffer_mgr.flush();
    log_mgr.chkp({2,3});

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    buffer_mgr.fake_flush();
  }

  return 0;
}

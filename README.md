# IIC3413-DB

## Project Build

Install Dependencies:
--------------------------------------------------------------------------------
MillenniumDB needs the following dependencies:
- GCC >= 8.1
- CMake >= 3.12

On recent Debian and Ubuntu based distributions they can be installed by running:
```bash
sudo apt update && sudo apt install g++ cmake
```

For Mac you need to install the **Xcode Command Line Tools** and [Homebrew](https://brew.sh/). After installing homebrew you can install cmake:
```bash
brew install cmake
```

Build the Project:
--------------------------------------------------------------------------------
Open a terminal in the project root directory, then execute the commands:

For the Release version:
```bash
cmake -Bbuild/Release -DCMAKE_BUILD_TYPE=Release && cmake --build build/Release/
```

For the Debug Version:
```bash
cmake -Bbuild/Debug -DCMAKE_BUILD_TYPE=Debug && cmake --build build/Debug/
```

To use multiple cores during compilation (much faster) add `-j n` at the end of the previous commands, replacing `n` with the desired number of threads. Example for 8 threads:
```bash
cmake -Bbuild/Debug -DCMAKE_BUILD_TYPE=Debug && cmake --build build/Debug/ -j 8
```

Test for lab 5:
--------------------------------------------------------------------------------

We provide an example database and some queries to show how to do tests for this lab.

First delete the old database if you have one:

Then create the test databases:
```bash
build/Debug/bin/create_test1
build/Debug/bin/create_test2
build/Debug/bin/create_test3
build/Debug/bin/create_test4
```

This creates the database folders `data/tests/t1`,`data/tests/t2`,`data/tests/t3` and `data/tests/t4`

You can check the state of a database using the command `print_tables`:
```bash
build/Debug/bin/print_tables data/tests/t1
```

And you can check the log using the command `print_log`:
```bash
build/Debug/bin/print_log data/tests/t1
```

To execute the recovery, use `simple_recovery` or `chkp_recovery` depending on what case you want to test:
```bash
build/Debug/bin/simple_recovery data/tests/t1
build/Debug/bin/simple_recovery data/tests/t2
build/Debug/bin/simple_recovery data/tests/t3
build/Debug/bin/chkp_recovery data/tests/t4
```

After a recovery, use `print_tables` to check the new state of the database.
If something failed you need to remove the database folder and generate it to test again.

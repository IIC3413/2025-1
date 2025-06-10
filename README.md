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

Test for lab 4:
--------------------------------------------------------------------------------

We provide an example database and some queries to show how to do tests for this lab.

First delete the old database if you have one:

```bash
rm -r data/test_example
```

Then create the database:
```bash
build/Debug/bin/create_db
```

Now you can execute a query passing the query folder as first parameter and the query file as second parameter, add `--explain` to print the logical plan and physical plans:
```bash
build/Debug/bin/execute_query data/test_example/ data/query1.sql --explain
```

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

Grammar Generation:
--------------------------------------------------------------------------------

To generate the necessary grammar files do one of the following:

- In the `src/query/parser/grammar` directory run the shell script
  `generate.sh`. This require you to have Java installed in your machine.

- Build the provided docker image and run it using the next two commands:
  ```
  docker build -f Dockerfile.Parser -t iic3413db-parser .
  docker run --rm -v $(pwd)/src/query/parser/grammar/:/src/query/parser/grammar iic3413db-parser
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

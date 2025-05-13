cmake_minimum_required(VERSION 3.12)

# Set project name and version
project(IIC3413DB VERSION 0.2.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable export of compile commands output
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set output directories
set(EXECUTABLE_OUTPUT_PATH bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib)

# Define the compiler flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -pthread -funroll-loops -fno-operator-names")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g3 -fsanitize=undefined,address -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -g0")

# When compiling with Clang generate debug info specifically for lldb
if(CMAKE_CXX_COMPILER_ID STREQUAL Clang)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -glldb -fstandalone-debug")
endif()

if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated")
    set(FS "")
else()
    set(FS "stdc++fs")
endif(APPLE)

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/src)

# Define sources
file(GLOB_RECURSE SRCS src/*.cc src/*.cpp)
file(GLOB_RECURSE BIN_SRCS src/bin/*.cc)

# Remove unwanted files from common sources
list(REMOVE_ITEM SRCS ${BIN_SRCS})

# Third party dependencies
add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/antlr4-runtime-4.13.1)
include_directories(${CMAKE_SOURCE_DIR}/third_party/antlr4-runtime-4.13.1/src)

# Define targets
add_library(iic3413db STATIC ${SRCS})
target_compile_definitions(iic3413db PUBLIC SERD_STATIC)

set(BUILD_TARGETS
    create_db
    create_table
    insert
    print_table
	execute_query
)

# Build targets
foreach(target ${BUILD_TARGETS})
    add_executable(${target} ${CMAKE_SOURCE_DIR}/src/bin/${target}.cc)
    target_link_libraries(${target}
        iic3413db
        antlr4_cpp_runtime
        ${FS}
    )
endforeach(target)

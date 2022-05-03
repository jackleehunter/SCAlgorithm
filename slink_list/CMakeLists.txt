
cmake_minimum_required(VERSION 3.10)
project(slinklist)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-g -fPIC -pthread")

# aux_source_directory(${PROJECT_SOURCE_DIR}/src NETCASE_SRC)
# aux_source_directory(${PROJECT_SOURCE_DIR}/unit_test UNITTEST_SRC)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(slinklist ./unit_test/unit_test.cc ./src/sc_slink_iterator.cc)
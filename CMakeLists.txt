cmake_minimum_required(VERSION 3.10)
project(ChronoSync CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(include)

file(GLOB LIB_SRC src/*.cpp)
list(REMOVE_ITEM LIB_SRC ${CMAKE_SOURCE_DIR}/src/main.cpp)
add_library(chronosync_lib ${LIB_SRC})

add_executable(chronosync src/main.cpp)
target_link_libraries(chronosync chronosync_lib)

add_executable(chronosync_tests tests/test_main.cpp)
target_link_libraries(chronosync_tests chronosync_lib)

add_executable(chronosync_bench benchmark/benchmark.cpp)
target_link_libraries(chronosync_bench chronosync_lib)

enable_testing()
add_test(NAME unit_tests COMMAND chronosync_tests)

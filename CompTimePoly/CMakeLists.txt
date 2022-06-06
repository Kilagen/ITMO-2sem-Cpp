cmake_minimum_required(VERSION 3.21)
project(CompTimePoly)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(gtest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
# 'main.cpp poly.h' are source files with tests
add_executable(Google_Tests_run main.cpp poly.h)
target_link_libraries(Google_Tests_run gtest gtest_main)

cmake_minimum_required(VERSION 3.21)
project(MyAllocator)

set(CMAKE_CXX_STANDARD 20)

add_executable(MyAllocator main.cpp MyAlloc.h MyMemoryManager.cpp MyMemoryManager.h)

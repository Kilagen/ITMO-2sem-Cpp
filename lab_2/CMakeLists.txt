cmake_minimum_required(VERSION 3.21)
project(Lab2)

set(CMAKE_CXX_STANDARD 17)

# I'm unable to use local path :(
set(libcurl_INCLUDE_DIR "C:/Users/kil4g/CLionProjects/lab_2/curl-7.82.0-win64-mingw/include")
include_directories(${libcurl_INCLUDE_DIR})


add_executable(Lab2 main.cpp CurrencyIO.cpp CurrencyIO.h)
add_executable(counter statCalc.cpp Stat.cpp Stat.h CurrencyIO.cpp CurrencyIO.h)

# I'm unable to use local path :(
target_link_libraries(Lab2 C:/Users/kil4g/CLionProjects/lab_2/curl-7.82.0-win64-mingw/lib/libcurl.dll.a)

set(CMAKE_EXE_LINKER_FLAGS "-static")
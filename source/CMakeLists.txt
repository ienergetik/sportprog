cmake_minimum_required(VERSION 3.21)
project(today)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -Wshadow -D_GLIBCXX_DEBUG -D_DEBUG")
add_executable(today main.cpp debug.h)
add_executable(gen gen.cpp)

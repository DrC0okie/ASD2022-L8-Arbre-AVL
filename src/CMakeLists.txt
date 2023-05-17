cmake_minimum_required(VERSION 3.15)
project(ASD2022_L8_AVL_Tree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion -Wsign-conversion -pedantic")

add_executable(AVL-Tree main.cpp)
add_subdirectory(catch2_tests)
cmake_minimum_required(VERSION 3.21)
project(LRU_C)

set(CMAKE_CXX_STANDARD 23)

add_executable(LRU_C main.cpp LRU.h LRU.cpp)

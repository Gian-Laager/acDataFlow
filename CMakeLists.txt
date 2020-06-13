cmake_minimum_required(VERSION 3.16)
project(acDataFlow)

set(CMAKE_CXX_STANDARD 17)

add_library(acDataFlow ${CMAKE_CURRENT_LIST_DIR}/src/acDataFlow.cpp ${CMAKE_CURRENT_LIST_DIR}/include/acDataFlow.h)
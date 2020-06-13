cmake_minimum_required(VERSION 3.16)
project(acDataFlow)

set(CMAKE_CXX_STANDARD 17)

set(SRC_FILES
        ${CMAKE_CURRENT_LIST_DIR}/helloWorld.cpp
        )

include_directories(${CMAKE_CURRENT_LIST_DIR}/../../include)

add_executable(acDataFlowHelloWorld ${CMAKE_CURRENT_LIST_DIR}/helloWorld.cpp)

target_link_libraries(acDataFlowHelloWorld ${CMAKE_CURRENT_LIST_DIR}/../../cmake-build-debug/libacDataFlow.a)
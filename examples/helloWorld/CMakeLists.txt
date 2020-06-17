cmake_minimum_required(VERSION 3.16)
project(acDataFlow)

set(CMAKE_CXX_STANDARD 17)

set(SRC_FILES
        ${CMAKE_CURRENT_LIST_DIR}/helloWorld.cpp
        )

set(AC_DATA_FLOW_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/../..)
include_directories(${AC_DATA_FLOW_ROOT_DIR}/include)

include(${AC_DATA_FLOW_ROOT_DIR}/CMakeLists.txt)

add_executable(acDataFlowHelloWorld ${CMAKE_CURRENT_LIST_DIR}/helloWorld.cpp)

target_link_libraries(acDataFlowHelloWorld ${AC_DATA_FLOW_ROOT_DIR}/cmake-build-debug/libacDataFlow.a)
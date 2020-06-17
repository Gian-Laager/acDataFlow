cmake_minimum_required(VERSION 3.16.2)

project(acDataFlow)

set(CMAKE_CXX_STANDARD 17)

if (NOT DEFINED AC_DATA_FLOW_ROOT_DIR)
    message(WARNING "AC_DATA_FLOW_ROOT_DIR will be ${CMAKE_CURRENT_LIST_DIR}, if you're not running the CMakeLists.txt in the root dir of the acDataFlow library, please set the variable AC_DATA_FLOW_ROOT_DIR to the path to the root of the acDataFlow library")   #only for Gian Laager, normally the user will set this variable
    set(AC_DATA_FLOW_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})
endif ()

set(SRC_FILES
        ${AC_DATA_FLOW_ROOT_DIR}/src/acDataFlow.cpp
        )

set(HEADER_FILES
        ${AC_DATA_FLOW_ROOT_DIR}/include/acDataFlow.h
        )

include_directories(${AC_DATA_FLOW_ROOT_DIR}/include)

set(Boost_INCLUDE_DIR ${AC_DATA_FLOW_ROOT_DIR}/deps/boost)
include_directories(${AC_DATA_FLOW_ROOT_DIR}/deps/boost)

include_directories(${AC_DATA_FLOW_ROOT_DIR}/deps/SYCL/include)

add_library(acDataFlow ${SRC_FILES} ${HEADER_FILES})
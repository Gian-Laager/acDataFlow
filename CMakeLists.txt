cmake_minimum_required(VERSION 3.16.2)
project(acDataFlow)

if (NOT DEFINED AC_DATA_FLOW_ROOT_DIR)
    message(STATUS "AC_DATA_FLOW_ROOT_DIR will be ${CMAKE_CURRENT_LIST_DIR}, if you're not running the CMakeLists.txt in the root dir of the acDataFlow library, please set the variable AC_DATA_FLOW_ROOT_DIR to the path to the root of the acDataFlow library")
    set(AC_DATA_FLOW_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})
endif()

if (DEFINED GIAN_LAAGERS_MAC)
    set(CMAKE_GNUC_COMPILER /usr/local/Cellar/gcc@8/8.4.0_1/bin/gcc-8)
    set(CMAKE_GNUCXX_COMPILER /usr/local/Cellar/gcc@8/8.4.0_1/bin/g++-8)
    message(STATUS ${GIAN_LAAGERS_MAC})
endif()

set(CMAKE_CXX_COMPILER_FLAG -fopenmp)
set(CMAKE_C_COMPILER_FLAG -fopenmp)

set(CMAKE_COMPILER_IS_GNUCXX "1")

set(CMAKE_CXX_STANDARD 17)

set(SRC_FILES
        ${AC_DATA_FLOW_ROOT_DIR}/src/acDataFlow.cpp
        )

set(HEADER_FILES
        ${AC_DATA_FLOW_ROOT_DIR}/include/acDataFlow.h
        )

set(Boost_INCLUDE_DIR  ${AC_DATA_FLOW_ROOT_DIR}/deps/boost)

include_directories(${AC_DATA_FLOW_ROOT_DIR}/include)

set(TRISYCL_OPENCL "1")
set(TRISYCL_INCLUDE_DIR ${AC_DATA_FLOW_ROOT_DIR}/deps/SYCL/include)

include(${AC_DATA_FLOW_ROOT_DIR}/deps/SYCL/CMakeLists.txt)
include_directories(${AC_DATA_FLOW_ROOT_DIR}/deps/SYCL/include)

find_package(OpenCL)

if(DEBUG)
    add_library(acDataFlow ${SRC_FILES} ${HEADER_FILES})
elseif(RELEASE)
    add_library(acDataFlow ${SRC_FILES} ${HEADER_FILES})
endif()

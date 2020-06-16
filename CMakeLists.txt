cmake_minimum_required(VERSION 3.16.2)
project(acDataFlow)

if (NOT DEFINED AC_DATA_FLOW_ROOT_DIR)
    message(WARNING "AC_DATA_FLOW_ROOT_DIR will be ${CMAKE_CURRENT_LIST_DIR}, if you're not running the CMakeLists.txt in the root dir of the acDataFlow library, please set the variable AC_DATA_FLOW_ROOT_DIR to the path to the root of the acDataFlow library")   #only for Gian Laager, normally the user will set this variable
    set(AC_DATA_FLOW_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})
endif ()

if (DEFINED GIAN_LAAGERS_MAC)
    set(CMAKE_C_COMPILER "/usr/bin/clang")
    set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
    set(CMAKE_CXX_COMPILER_ID Clang)
    set(CMAKE_C_COMPILER_ID Clang)

    set(OPENMP_LIBRARIES "/usr/local/opt/llvm/lib")
    set(OPENMP_INCLUDES "/usr/local/opt/llvm/include")

    link_directories(${OPENMP_LIBRARIES})
    message(STATUS ${GIAN_LAAGERS_MAC})
endif ()

set(OpenMP_C "${CMAKE_C_COMPILER}")
set(OpenMP_C_FLAGS "-fopenmp=libomp -Wno-unused-command-line-argument")
set(OpenMP_C_LIB_NAMES "libomp" "libgomp" "libiomp5")
set(OpenMP_libomp_LIBRARY ${OpenMP_C_LIB_NAMES})
set(OpenMP_libgomp_LIBRARY ${OpenMP_C_LIB_NAMES})
set(OpenMP_libiomp5_LIBRARY ${OpenMP_C_LIB_NAMES})
set(OpenMP_CXX "${CMAKE_CXX_COMPILER}")
set(OpenMP_CXX_FLAGS "-fopenmp=libomp -Wno-unused-command-line-argument")
set(OpenMP_CXX_LIB_NAMES "libomp" "libgomp" "libiomp5")
set(OpenMP_libomp_LIBRARY ${OpenMP_CXX_LIB_NAMES})
set(OpenMP_libgomp_LIBRARY ${OpenMP_CXX_LIB_NAMES})
set(OpenMP_libiomp5_LIBRARY ${OpenMP_CXX_LIB_NAMES})

#set(CMAKE_COMPILER_IS_GNUCXX "ON")

set(CMAKE_CXX_STANDARD 17)

set(SRC_FILES
        ${AC_DATA_FLOW_ROOT_DIR}/src/acDataFlow.cpp
        )

set(HEADER_FILES
        ${AC_DATA_FLOW_ROOT_DIR}/include/acDataFlow.h
        )

set(Boost_INCLUDE_DIR ${AC_DATA_FLOW_ROOT_DIR}/deps/boost)

include_directories(${AC_DATA_FLOW_ROOT_DIR}/include)

set(TRISYCL_OPENCL "ON")
if (CMAKE_DEBUG)
    set(TRISYCL_DEBUG "ON")
endif ()
set(TRISYCL_INCLUDE_DIR ${AC_DATA_FLOW_ROOT_DIR}/deps/SYCL/include)

include(${AC_DATA_FLOW_ROOT_DIR}/deps/SYCL/CMakeLists.txt)
include_directories(${AC_DATA_FLOW_ROOT_DIR}/deps/SYCL/include)

find_package(OpenCL)
add_library(acDataFlow ${SRC_FILES} ${HEADER_FILES})
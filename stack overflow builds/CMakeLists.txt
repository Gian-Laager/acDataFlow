cmake_minimum_required(VERSION 3.16.2)

project(acMandelbrotSet_stackoverflow)

set(CMAKE_CXX_STANDARD 17)

set(SRC_FILES
        ${CMAKE_CURRENT_LIST_DIR}/stackoverflow.cpp
        )

include_directories(${CMAKE_CURRENT_LIST_DIR})

find_package(OpenCL REQUIRED)

set(Boost_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/../deps/boost)
include_directories(${Boost_INCLUDE_DIR})

include_directories(${CMAKE_CURRENT_LIST_DIR}/../deps/SYCL/include)

set(LIBS PRIVATE ${Boost_LIBRARIES} OpenCL::OpenCL)

add_executable(${PROJECT_NAME} ${SRC_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX _d)
target_link_libraries(${PROJECT_NAME} ${LIBS})
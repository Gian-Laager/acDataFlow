# Copyright 2018 Mike Dev
# Copyright 2019 Peter Dimov
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

cmake_minimum_required(VERSION 3.5...3.16)
project(boost_atomic VERSION "${BOOST_SUPERPROJECT_VERSION}" LANGUAGES CXX)

add_library(boost_atomic src/lock_pool.cpp)
add_library(Boost::atomic ALIAS boost_atomic)

target_include_directories(boost_atomic PUBLIC include)

target_link_libraries(boost_atomic
  PUBLIC
    Boost::assert
    Boost::config
    Boost::type_traits
)

target_compile_definitions(boost_atomic
  PUBLIC
    BOOST_ATOMIC_NO_LIB
  PRIVATE
    BOOST_ATOMIC_SOURCE
)

if(BUILD_SHARED_LIBS)
  target_compile_definitions(boost_atomic PUBLIC BOOST_ATOMIC_DYN_LINK)
else()
  target_compile_definitions(boost_atomic PUBLIC BOOST_ATOMIC_STATIC_LINK)
endif()

if(BOOST_SUPERPROJECT_VERSION)

  include(BoostInstall)
  boost_install(TARGETS boost_atomic HEADER_DIRECTORY include/)

endif()

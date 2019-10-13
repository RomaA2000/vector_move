cmake_minimum_required(VERSION 3.14)
project(vector_move)

set(CMAKE_CXX_STANDARD 17)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -flto -Wall -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
endif()

add_executable(vector_testing
        vector_testing.cpp
        counted.hpp
        vector.hpp
        counted.cpp
        fault_injection.hpp
        fault_injection.cpp
        gtest/gtest-all.cc
        gtest/gtest.h
        gtest/gtest_main.cc)

cmake_minimum_required(VERSION 3.26)
project(ray_tracer_challenge)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest CONFIG REQUIRED)


add_executable(ray_tracer_challenge main.cpp
        Tuple.cpp
        Tuple.h
        util.h
        color.cpp
        color.h)
add_executable(ray_tracer_challenge_test test.cpp
        Tuple.cpp
        Tuple.h
        util.h
        color.cpp
        color.h)

target_link_libraries(ray_tracer_challenge_test PRIVATE GTest::gtest GTest::gtest_main)

cmake_minimum_required(VERSION 3.26)
project(ray_tracer_challenge)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest CONFIG REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/src)
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB TEST_FILES ${PROJECT_SOURCE_DIR}/tests/*.cpp)

add_executable(ray_tracer_challenge ${PROJECT_SOURCE_DIR}/main.cpp ${SRC_FILES})

add_executable(ray_tracer_challenge_test ${TEST_FILES} ${SRC_FILES})

target_link_libraries(ray_tracer_challenge_test PRIVATE GTest::gtest GTest::gtest_main)

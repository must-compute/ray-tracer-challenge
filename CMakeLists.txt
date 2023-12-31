cmake_minimum_required(VERSION 3.26)
project(ray_tracer_challenge)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest CONFIG REQUIRED)
find_package(benchmark REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/src)
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB TEST_FILES ${PROJECT_SOURCE_DIR}/tests/*.cpp)

# to get stack traces
#set(CMAKE_BUILD_TYPE Debug)

add_executable(ray_tracer_challenge ${PROJECT_SOURCE_DIR}/main.cpp ${SRC_FILES})

add_executable(ray_tracer_challenge_test ${TEST_FILES} ${SRC_FILES})
target_link_libraries(ray_tracer_challenge_test PRIVATE GTest::gtest GTest::gtest_main)

add_executable(render_benchmark ${PROJECT_SOURCE_DIR}/render_benchmark.cpp ${SRC_FILES})
target_link_libraries(render_benchmark PRIVATE benchmark::benchmark)

# Making the canvas too big might exceed the stack size limit. With clang, using this sanitizer
# option will detect the issue.
#target_compile_options(ray_tracer_challenge PRIVATE -fsanitize=address)
#target_link_options(ray_tracer_challenge PRIVATE -fsanitize=address)


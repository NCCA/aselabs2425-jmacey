cmake_minimum_required(VERSION 3.20)

project(RGBA_build)

set(CMAKE_CXX_STANDARD 17)


add_executable(RGBA)
# add src/main.cpp to target RGBA
target_include_directories(RGBA PRIVATE include)
target_sources(RGBA PRIVATE ${CMAKE_SOURCE_DIR}/src/main.cpp )

## add another target for our tests

find_package(GTest CONFIG REQUIRED)
include(GoogleTest)
enable_testing()
add_executable(RGBATests)
target_include_directories(RGBATests PRIVATE include)

target_sources(RGBATests PRIVATE ${CMAKE_SOURCE_DIR}/tests/RGBATests.cpp)
target_link_libraries(RGBATests PRIVATE GTest::gtest GTest::gtest_main )

gtest_discover_tests(RGBATests)

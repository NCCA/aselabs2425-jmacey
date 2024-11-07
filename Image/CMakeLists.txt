cmake_minimum_required(VERSION 3.20)

project(Image_build)

set(CMAKE_CXX_STANDARD 17)
## add another target for our tests
find_package(OpenImageIO CONFIG REQUIRED)
find_package(Boost COMPONENTS filesystem thread)


add_executable(Image)
# add src/main.cpp to target RGBA
target_include_directories(Image PRIVATE include)
target_sources(Image PRIVATE ${CMAKE_SOURCE_DIR}/src/main.cpp ${CMAKE_SOURCE_DIR}/src/Image.cpp )
target_link_libraries(Image PRIVATE OpenImageIO::OpenImageIO Boost::filesystem Boost::thread )


find_package(GTest CONFIG REQUIRED)
include(GoogleTest)
enable_testing()
add_executable(ImageTests)
target_include_directories(ImageTests PRIVATE include)

target_sources(ImageTests PRIVATE ${CMAKE_SOURCE_DIR}/tests/ImageTests.cpp
                                  ${CMAKE_SOURCE_DIR}/tests/RGBATests.cpp
                                  ${CMAKE_SOURCE_DIR}/src/Image.cpp
                                  ${CMAKE_SOURCE_DIR}/include/Image.h
)
target_link_libraries(ImageTests PRIVATE GTest::gtest GTest::gtest_main )
target_link_libraries(ImageTests PRIVATE OpenImageIO::OpenImageIO Boost::filesystem Boost::thread )
gtest_discover_tests(ImageTests)

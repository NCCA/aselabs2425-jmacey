cmake_minimum_required(VERSION 3.20)

project(DLA_build)

set(CMAKE_CXX_STANDARD 17)
## add another target for our tests
find_package(OpenImageIO CONFIG REQUIRED)
find_package(Boost COMPONENTS filesystem thread)
find_package(fmt CONFIG REQUIRED)
find_package(cxxopts CONFIG REQUIRED)

add_executable(DLA)
# add src/main.cpp to target RGBA
target_include_directories(DLA PRIVATE include)
target_sources(DLA PRIVATE
                            ${CMAKE_SOURCE_DIR}/src/main.cpp
                            ${CMAKE_SOURCE_DIR}/src/Image.cpp
                            ${CMAKE_SOURCE_DIR}/src/Walker.cpp
                            ${CMAKE_SOURCE_DIR}/include/Image.h
                            ${CMAKE_SOURCE_DIR}/include/RGBA.h
                            ${CMAKE_SOURCE_DIR}/include/Walker.h
)
target_link_libraries(DLA PRIVATE OpenImageIO::OpenImageIO Boost::filesystem Boost::thread )
target_link_libraries(DLA PRIVATE fmt::fmt-header-only)
target_link_libraries(DLA PRIVATE cxxopts::cxxopts)












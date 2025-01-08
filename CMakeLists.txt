cmake_minimum_required(VERSION 3.10)

project(HuffmanEncoding VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(SOURCE "main.cpp" CACHE STRING "User-specified source file")

include_directories(
    ${PROJECT_SOURCE_DIR}/inc
)

file(GLOB_RECURSE LIB_SOURCE_FILES src/*.cpp)

set(CMAKE_BUILD_TYPE Release)

add_library(HuffmanEncodingLib ${LIB_SOURCE_FILES})

add_executable(HuffmanEncodingApp ${SOURCE})

target_link_libraries(HuffmanEncodingApp HuffmanEncodingLib)

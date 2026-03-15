cmake_minimum_required(VERSION 3.25)
project(ThreadedBinarySearchTree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(tbst
    ass5.cpp
    threadedBST.cpp
)

target_include_directories(tbst PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_options(tbst PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

cmake_minimum_required(VERSION 3.25)
project(ThreadedBinarySearchTree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(tbst
    ass5.cpp
    threadedBST.cpp
)

add_executable(tbst_tests
    tests.cpp
    threadedBST.cpp
)

target_include_directories(tbst PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(tbst_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_options(tbst PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

target_compile_options(tbst_tests PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

cmake_minimum_required(VERSION 3.14)
project(path_project)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the main library
add_library(path_lib
    path.cpp
    path.hpp
)

# Google Test setup
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Add the test executable
add_executable(path_tests
    tests/path_test.cpp
)

target_link_libraries(path_tests
    PRIVATE
    path_lib
    GTest::gtest_main
)

# Include Google Test
include(GoogleTest)
gtest_discover_tests(path_tests) 
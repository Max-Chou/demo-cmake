cmake_minimum_required(VERSION 3.14)
project(path_project)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories for all builds
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Handle MSVC specific settings
if(MSVC)
    # Enable parallel builds
    add_compile_options(/MP)
    # Disable warnings about secure functions
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    # Use static runtime library
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# Add the main library
add_library(path_lib
    path.cpp
    path.hpp
)

# Set include directories for the library
target_include_directories(path_lib
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Google Test setup
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
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

# Install rules
install(TARGETS path_lib
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(FILES path.hpp
    DESTINATION include
) 
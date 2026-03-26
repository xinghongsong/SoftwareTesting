cmake_minimum_required(VERSION 3.20)
project(CLion_Software_Testing)

set(CMAKE_CXX_STANDARD 17)

# 添加 Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(TriangleDemo main.cpp Triangle.cpp)

add_executable(TriangleTests
        TriangleTest.cpp
        Triangle.cpp
)

# 链接 Google Test 库
target_link_libraries(TriangleTests gtest_main)

# 启用 CMake 测试
enable_testing()
add_test(NAME TriangleTests COMMAND TriangleTests)
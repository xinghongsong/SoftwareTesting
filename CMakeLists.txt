cmake_minimum_required(VERSION 3.20)
project(TriangleExp2)

set(CMAKE_CXX_STANDARD 17)

# 自动下载 GoogleTest
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

# 添加三角形逻辑库（只包含 Triangle.cpp 和 Triangle.h）
add_library(TriangleLib STATIC
        Triangle.cpp
        Triangle.h
)

# 添加测试可执行文件（只包含 test_exp2.cpp）
add_executable(TriangleTests
        test_exp2.cpp
)

target_link_libraries(TriangleTests
        TriangleLib
        gtest_main
)

enable_testing()
add_test(NAME TriangleTests COMMAND TriangleTests)
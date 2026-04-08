cmake_minimum_required(VERSION 3.20)
project(YesterDate)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 启用代码覆盖率
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")

# 自动下载 Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# 将 yesterdate.cpp 编译成静态库（注意：这里只有这一个源文件）
add_library(YesterDateLib STATIC yesterdate.cpp)
target_include_directories(YesterDateLib PUBLIC .)

# 将 test.cpp 编译成测试可执行文件
add_executable(YesterDateTest test.cpp)
target_link_libraries(YesterDateTest YesterDateLib gtest_main)
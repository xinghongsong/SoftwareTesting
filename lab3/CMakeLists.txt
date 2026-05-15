cmake_minimum_required(VERSION 3.20)
project(PhoneBillExp3)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

# 只包含业务代码，不要包含测试文件
add_library(BillLib STATIC
        PhoneBill.cpp
        PhoneBill.h
)

# 测试可执行文件只包含 test_exp3.cpp
add_executable(BillTests
        test_exp3.cpp
)

target_link_libraries(BillTests
        BillLib
        gtest_main
)

enable_testing()
add_test(NAME BillTests COMMAND BillTests)

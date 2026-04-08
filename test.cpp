// Copyright (c) 2025. All rights reserved.
#include <gtest/gtest.h>
#include <stdexcept>
#include "yesterdate.h"

using yesterdate::YesterDate;

// 普通日：day > 1
TEST(YesterDateTest, OrdinaryDay) {
    auto [y, m, d] = YesterDate(2025, 3, 10);
    EXPECT_EQ(y, 2025);
    EXPECT_EQ(m, 3);
    EXPECT_EQ(d, 9);
}

// 3月1日 → 2月28日（平年）
TEST(YesterDateTest, MarchFirst) {
    auto [y, m, d] = YesterDate(2025, 3, 1);
    EXPECT_EQ(y, 2025);
    EXPECT_EQ(m, 2);
    EXPECT_EQ(d, 28);
}

// 1月1日 → 跨年到12月31日
TEST(YesterDateTest, NewYearDay) {
    auto [y, m, d] = YesterDate(2025, 1, 1);
    EXPECT_EQ(y, 2024);
    EXPECT_EQ(m, 12);
    EXPECT_EQ(d, 31);
}

// 闰年2月29日的前一天
TEST(YesterDateTest, Feb29InLeapYear) {
    auto [y, m, d] = YesterDate(2024, 2, 29);
    EXPECT_EQ(y, 2024);
    EXPECT_EQ(m, 2);
    EXPECT_EQ(d, 28);
}

// 非法输入测试
TEST(YesterDateDeathTest, InvalidYear) {
    EXPECT_THROW(YesterDate(1899, 1, 1), std::invalid_argument);
    EXPECT_THROW(YesterDate(2051, 1, 1), std::invalid_argument);
}

TEST(YesterDateDeathTest, InvalidMonth) {
    EXPECT_THROW(YesterDate(2025, 0, 15), std::invalid_argument);
    EXPECT_THROW(YesterDate(2025, 13, 15), std::invalid_argument);
}

TEST(YesterDateDeathTest, InvalidDay) {
    EXPECT_THROW(YesterDate(2025, 2, 30), std::invalid_argument);
    EXPECT_THROW(YesterDate(2025, 4, 31), std::invalid_argument);
}
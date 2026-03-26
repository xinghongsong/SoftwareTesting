#include <gtest/gtest.h>
#include "Triangle.h"

// 测试：一般三角形
TEST(TriangleTest, ScaleneTriangle) {
    EXPECT_EQ(classifyTriangle(3, 4, 6), "一般三角形");
}

// 测试：等边三角形
TEST(TriangleTest, EquilateralTriangle) {
    EXPECT_EQ(classifyTriangle(3, 3, 3), "等边三角形");
}

// 测试：非三角形
TEST(TriangleTest, NotTriangle) {
    EXPECT_EQ(classifyTriangle(3, 3, 6), "非三角形");
}

// 测试：等腰三角形
TEST(TriangleTest, IsoscelesTriangle) {
    EXPECT_EQ(classifyTriangle(5, 5, 8), "等腰三角形");
}

// 测试：输入非法（超出范围）
TEST(TriangleTest, InvalidInput) {
    EXPECT_EQ(classifyTriangle(0, 5, 5), "输入错误");
    EXPECT_EQ(classifyTriangle(101, 50, 50), "输入错误");
}

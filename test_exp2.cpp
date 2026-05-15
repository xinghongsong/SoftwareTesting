#include <gtest/gtest.h>
#include "Triangle.h"
#include <vector>
#include <string>

// 定义一个结构体，存放测试用例的输入和期望输出
struct TestCase {
    int a, b, c;
    std::string expected;
};

// 参数化测试的基类
class BoundaryTest : public ::testing::TestWithParam<TestCase> {};

// 测试主体：比较 classify 的输出是否与期望一致
TEST_P(BoundaryTest, CheckBoundary) {
    const TestCase& param = GetParam();
    EXPECT_EQ(classify(param.a, param.b, param.c), param.expected);
}

// 辅助函数：生成单变量变化（一个变量取集合中的每个值，另两个固定为 normal）
std::vector<TestCase> generateSingleVariable(const std::vector<int>& values, int normal) {
    std::vector<TestCase> cases;
    for (int v : values) {
        cases.push_back({v, normal, normal, classify(v, normal, normal)});
        cases.push_back({normal, v, normal, classify(normal, v, normal)});
        cases.push_back({normal, normal, v, classify(normal, normal, v)});
    }
    return cases;
}

// 辅助函数：生成全组合（三个变量独立取 values 中的每个值）
std::vector<TestCase> generateCombination(const std::vector<int>& values) {
    std::vector<TestCase> cases;
    for (int a : values) {
        for (int b : values) {
            for (int c : values) {
                cases.push_back({a, b, c, classify(a, b, c)});
            }
        }
    }
    return cases;
}

// 定义边界值集合
const std::vector<int> GENERAL_VALS = {1, 2, 50, 99, 100};
const std::vector<int> ROBUST_VALS = {0, 1, 2, 50, 99, 100, 101};
const int NORMAL = 50;

// 1. 一般边界值（单变量变化，15个用例）
INSTANTIATE_TEST_SUITE_P(
    GeneralBoundary,
    BoundaryTest,
    ::testing::ValuesIn(generateSingleVariable(GENERAL_VALS, NORMAL))
);

// 2. 健壮性边界值（单变量变化，21个用例）
INSTANTIATE_TEST_SUITE_P(
    RobustBoundary,
    BoundaryTest,
    ::testing::ValuesIn(generateSingleVariable(ROBUST_VALS, NORMAL))
);

// 3. 最坏情况一般边界值（全组合，125个用例）
INSTANTIATE_TEST_SUITE_P(
    WorstGeneral,
    BoundaryTest,
    ::testing::ValuesIn(generateCombination(GENERAL_VALS))
);

// 4. 最坏情况健壮性边界值（全组合，343个用例）
INSTANTIATE_TEST_SUITE_P(
    WorstRobust,
    BoundaryTest,
    ::testing::ValuesIn(generateCombination(ROBUST_VALS))
);
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "PhoneBill.h"

struct BillTestCase {
    DateTime start;
    DateTime end;
    double expectedFee;
    std::string desc;
};

class BillTest : public ::testing::TestWithParam<BillTestCase> {};

TEST_P(BillTest, CheckBill) {
    const auto& param = GetParam();
    double fee = getPhoneBill(param.start, param.end);
    EXPECT_NEAR(fee, param.expectedFee, 0.01) << "Test: " << param.desc;
}

// 辅助创建DateTime
DateTime makeDT(int month, int day, int hour, int minute, int second) {
    return {2024, month, day, hour, minute, second};
}

// 定义测试数据
std::vector<BillTestCase> testCases = {
    // 1. 不跨夏令时，普通通话 <=20分钟
    {makeDT(3,1,10,0,0), makeDT(3,1,10,5,30), 0.30, "5.5分钟→6分钟*0.05=0.30"},
    {makeDT(5,5,8,0,0), makeDT(5,5,8,20,0), 1.00, "20分钟*0.05=1.00"},
    {makeDT(5,5,8,0,0), makeDT(5,5,8,19,59), 1.00, "19分59秒→20分钟*0.05=1.00"},
    // 2. 不跨夏令时，>20分钟
    {makeDT(5,5,8,0,0), makeDT(5,5,8,30,0), 2.00, "30分钟: 1.00+1.00=2.00"},
    {makeDT(5,5,8,0,0), makeDT(5,5,8,20,1), 1.10, "20分1秒→21分钟: 1.00+0.10=1.10"},
    // 3. 跨越春季夏令时（3月10日2:00->3:00）实际少一小时
    {makeDT(3,10,1,59,59), makeDT(3,10,3,0,0), 0.05, "跨春季，实际1分钟→0.05"},
    {makeDT(3,10,1,0,0), makeDT(3,10,3,1,0), 5.10, "跨越春季，实际61分钟→5.10"},
    // 4. 跨越秋季夏令时（11月3日2:00调回1:00，重复一小时）
    {makeDT(11,3,1,59,59), makeDT(11,3,2,1,0), 5.20, "跨越秋季，实际62分钟→5.20"},
    // 5. 无效：结束早于开始
    {makeDT(3,10,10,0,0), makeDT(3,10,9,0,0), -1.0, "结束早于开始"},
    // 6. 边界：通话0分钟
    {makeDT(4,15,12,0,0), makeDT(4,15,12,0,0), 0.0, "0分钟"},
};

INSTANTIATE_TEST_SUITE_P(
    PhoneBillTests,
    BillTest,
    ::testing::ValuesIn(testCases)
);

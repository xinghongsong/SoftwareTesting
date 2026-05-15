#ifndef PHONEBILL_H
#define PHONEBILL_H

#include <string>

struct DateTime {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

// 计算两个时间之间的实际通话分钟数（考虑夏令时跳过/重复）
// 返回值：分钟数（double），如果结束<开始返回 -1
double computeActualMinutes(const DateTime& start, const DateTime& end);

// 根据实际分钟数计算费用
double calculateFee(double minutes);

// 综合函数：给定开始和结束时间，直接返回费用（美元）
double getPhoneBill(const DateTime& start, const DateTime& end);

#endif
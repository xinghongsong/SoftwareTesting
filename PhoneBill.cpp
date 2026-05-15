#include "PhoneBill.h"
#include <cmath>
#include <ctime>

// 辅助函数：判断是否为闰年
static bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// 每个月的天数
static int daysInMonth(int year, int month) {
    static const int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (month == 2 && isLeapYear(year)) return 29;
    return days[month-1];
}

// 将 DateTime 转换为从某个基准点开始的秒数（简单实现，不考虑夏令时）
static long long toSeconds(const DateTime& dt) {
    long long total = 0;
    // 累加年份
    for (int y = 2000; y < dt.year; ++y) {
        total += isLeapYear(y) ? 366 : 365;
    }
    // 累加月份
    for (int m = 1; m < dt.month; ++m) {
        total += daysInMonth(dt.year, m);
    }
    // 累加天数、小时、分钟、秒
    total += (dt.day - 1);
    total = total * 24 + dt.hour;
    total = total * 60 + dt.minute;
    total = total * 60 + dt.second;
    return total;
}

// 判断是否在春季夏令时开始时刻之后（包含开始时刻）
// 为简化，我们固定2024年：春季转换 3月10日 02:00:00 -> 03:00:00
static bool isAfterDSTStart(const DateTime& dt) {
    if (dt.year != 2024) return false; // 仅处理2024年
    if (dt.month < 3) return false;
    if (dt.month > 3) return true;
    // 3月
    if (dt.day < 10) return false;
    if (dt.day > 10) return true;
    // 3月10日当天
    if (dt.hour < 2) return false;
    // 注意：2:00:00 那一瞬间变成3:00:00，所以2:00:00这一秒实际上不存在
    // 我们简化：大于等于3点算之后，2:00~2:59:59 不存在，但输入不会出现
    return dt.hour >= 3;
}

// 判断是否在秋季夏令时结束时刻之后（包含结束时刻）
// 2024年秋季转换 11月3日 02:00:00 调回 01:00:00，因此2:00-2:59:59会重复一次
// 我们需要判断时间是否在“第二次”2:00之后？为了简化，我们假设输入时间已经是处理过的标准时间
// 更实际的做法是：计算时间差时，如果跨越了结束点，则加上一小时（因为多了一小时）
static bool isAfterDSTEnd(const DateTime& dt) {
    if (dt.year != 2024) return false;
    if (dt.month < 11) return false;
    if (dt.month > 11) return true;
    if (dt.day < 3) return false;
    if (dt.day > 3) return true;
    // 11月3日当天，小时>=2 算之后（注意，2点出现了两次，但实际时间流逝是两次）
    return dt.hour >= 2;
}

// 计算实际分钟数
double computeActualMinutes(const DateTime& start, const DateTime& end) {
    long long startSec = toSeconds(start);
    long long endSec = toSeconds(end);
    if (endSec < startSec) return -1.0; // 错误

    // 基础秒数差
    long long diffSec = endSec - startSec;

    // 判断是否跨越春季夏令时开始（少一小时）
    // 条件：start 在 DST 开始之前，end 在 DST 开始之后
    // 春季 DST 开始时刻：2024-03-10 02:00:00（实际不存在，但作为边界）
    // 因为2:00跳到了3:00，所以实际流逝时间少了1小时（3600秒）
    if (start.year == 2024 && end.year == 2024) {
        // 春季
        DateTime dstStart = {2024,3,10,2,0,0};
        if (toSeconds(start) < toSeconds(dstStart) && toSeconds(end) >= toSeconds(dstStart)) {
            diffSec -= 3600; // 跳过了一小时
        }
        // 秋季
        DateTime dstEnd = {2024,11,3,2,0,0};
        if (toSeconds(start) < toSeconds(dstEnd) && toSeconds(end) >= toSeconds(dstEnd)) {
            diffSec += 3600; // 重复了一小时
        }
    }

    // 秒转分钟，向上取整（不足1分钟按1分钟）
    double minutes = ceil(diffSec / 60.0);
    return minutes;
}

double calculateFee(double minutes) {
    if (minutes <= 0) return 0.0;
    if (minutes <= 20) {
        return minutes * 0.05;
    } else {
        return 1.0 + (minutes - 20) * 0.10;
    }
}

double getPhoneBill(const DateTime& start, const DateTime& end) {
    double minutes = computeActualMinutes(start, end);
    if (minutes < 0) return -1.0; // 错误：结束时间早于开始
    return calculateFee(minutes);
}
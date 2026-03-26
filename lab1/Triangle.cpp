#include "Triangle.h"
#include <string>

std::string classifyTriangle(int a, int b, int c) {
    // 检查边长范围（1-100）
    if (a < 1 || a > 100 || b < 1 || b > 100 || c < 1 || c > 100) {
        return "输入错误";
    }
    
    // 检查三角形不等式
    if (!(a + b > c && a + c > b && b + c > a)) {
        return "非三角形";
    }
    
    // 分类
    if (a == b && b == c) {
        return "等边三角形";
    } else if (a == b || b == c || a == c) {
        return "等腰三角形";
    } else {
        return "一般三角形";
    }
}

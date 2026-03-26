#include <iostream>
#include "Triangle.h"

int main() {
    int a, b, c;
    std::cout << "请输入三角形的三条边：";
    std::cin >> a >> b >> c;

    std::string result = classifyTriangle(a, b, c);
    std::cout << "结果：" << result << std::endl;

    return 0;
}
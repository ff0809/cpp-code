#include<iostream>
using namespace std;

// 第一个函数，接收用户输入的距离d并返回
double myfunction1() {
    double d;
    cout << "请输入三体人到地球的距离（单位：光年，0 < d <= 100）: ";
    cin >> d;
    return d;
}

// 第二个函数，接收距离d并计算所需时间t
double myfunction2(double d) {
    return d / 0.01;
}

// 第三个函数，输出计算结果t
void myfunction3(double t) {
    cout << "三体人需要 " << t << " 年到达地球。" << endl;
}

int main() {
    double distance = myfunction1();
    double time = myfunction2(distance);
    myfunction3(time);
    return 0;
}

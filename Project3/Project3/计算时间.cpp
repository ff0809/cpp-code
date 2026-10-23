#include<iostream>
using namespace std;

double myfunction1() {
    double d;
    cin >> d;
    return 0;
}

double myfunction2() {
    double d;
    cin >> d;
    return d/0.01;
}
double myfunction3(){
    double t;
    cin >> t;
    cout << "三体人需要 " << t << " 天到达地球。" << endl;
    return 0;
}

int main() {
    myfunction1();
    myfunction2();
    myfunction3();
    return 0;
}
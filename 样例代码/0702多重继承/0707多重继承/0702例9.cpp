#include <iostream>  
using namespace std;
static int x = 0;
class A {
public:
    int a;
    A() { a = ++x; }
    void f1() { cout << a << endl; }
};
class B :public A {
public:
    int b;
};
class D :public B, public A {
public:
    int d;
    int fun();
};
int D::fun()
{
    A::a = 10; //不建议
    A::f1();   //不建议
    B::a = 15;
    B::f1();
    a = 15;   //报错：对a的访问不明确
    f1();     //报错：对f1的访问不明确
    return 0;
}
int main() {
    D d1;
    cout << sizeof(d1) << endl;
    d1.fun();
    d1.f1();   //报错：对f1的访问不明确
    d1.a = 15;  //报错：对a的访问不明确
    d1.A::a = 10; //不建议 
    d1.A::f1();   //不建议
    d1.B::a = 15;
    d1.B::f1();
    return 0;
}
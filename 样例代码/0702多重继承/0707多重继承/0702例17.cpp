#include <iostream>  
using namespace std;

class B; //提前声明 
class A {
public:
    int a;
    A() {} //无参空体 
    A(B& b);//不能体内实现
    A& operator=(B& b);//不能体内实现
};
class B :public A {
public:
    int b;
};
A::A(B& b) //一参构造
{
    a = b.a * 2;
}
A& A::operator=(B& b) //=重载
{
    a = b.a * 2;
    return (*this);
}
int main()
{
    B b1;
    b1.a = 15;
    A a1(b1), a2;
    //一参，无参构造
    a2 = b1; //= 重载
    cout << a1.a << endl; //30
    cout << a2.a << endl; //30
}

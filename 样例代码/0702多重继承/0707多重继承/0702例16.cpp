#include <iostream>  
using namespace std;

class A {
public:
    int a;
};
class B :public A {
public:
    int b;
};
int main()
{
    B b1;
    b1.a = 15;
    A a1(b1); //∏¥÷∆ππ‘Ï 
    A a2;
    a2 = b1;
    cout << a1.a << endl; //15
    cout << a2.a << endl; //15
}

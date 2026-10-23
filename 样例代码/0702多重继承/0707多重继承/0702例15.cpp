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
    A a1;
    B b1;
    a1.a = 10;
    b1.a = 15;
    cout << a1.a << endl;
    b1 = a1; //±àÒë´í!!!
    cout << a1.a << endl;
}


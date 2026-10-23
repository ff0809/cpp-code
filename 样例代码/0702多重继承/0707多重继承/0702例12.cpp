#include <iostream> 
using namespace std;
class A {
public:
	A() { cout << "A()" << endl; }
};
class B : virtual public A {
public:
	B() { cout << "B()" << endl; }
};
class C : virtual public A {
public:
	C() { cout << "C()" << endl; }
};
class D : public A {
public:
	D() { cout << "D()" << endl; }
};
class E :public B, public C, public D {
public:
	E() { cout << "E()" << endl; }
};
int main() {
	E e1;  //e1中有两份A的拷贝
}

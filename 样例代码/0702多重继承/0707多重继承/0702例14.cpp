#include <iostream> 
using namespace std;
class A {
public:
    A() { cout << "A()" << endl; } // 无参构造 
    A(int x) { cout << "A(" << x << ")" << endl; } //一参构造
};
class B :virtual public A {
public:
    B(int y) { cout << "B()" << endl; }
};
class C :virtual public A {
public:
    C(int z) :A(z) { cout << "C()" << endl; }
};
class D :public B, public C {
public:
    D(int x, int y, int z) :A(x), B(y), C(z) {
        cout << "D()" << endl;
    }
};
int main() {
    D d1(1, 2, 3);
    cout << endl;
    C c1(4);
    cout << endl;
    B b1(5);
}

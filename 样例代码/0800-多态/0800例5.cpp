//#include<iostream>
//using namespace std;
//class A {
//public:
//    virtual void display() {
//        cout << "A::display()" << endl;
//    }
//    void show() {
//        cout << "A::show()" << endl;
//    }
//};
//class B :public A {
//    void display() {
//        cout << "B::display()" << endl;
//    }
//    void show() {
//        cout << "B::show()" << endl;
//    };
//};
//
//class C :public B {
//public:
//    void display() {
//        cout << "C::display()" << endl;
//    }
//    void show() {
//        cout << "C::show()" << endl;
//    };
//};
//int main() {
//    A a, * p;
//    B b;
//    C c;
//    p = &a;
//    p->display();  // A::
//        p->show(); // A::
//        p = &b;
//    p->display();  // B::
//        p->show(); // A::
//        p = &c;
//    p->display();  // C::
//        p->show(); // A::
//}

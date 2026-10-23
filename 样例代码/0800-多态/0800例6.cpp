//#include <iostream>  
//using namespace std;
//class A {
//public:
//	virtual void display() {
//		cout << "A::display()" << endl;
//	}
//};
//class B :public A {
//public:
//	void display() {
//		cout << "B::display()" << endl;
//	}
//};
//class C :public B {
//public:
//	void display() {
//		cout << "C::display()" << endl;
//	}
//};
//int main() {
//    A a, & ra = a, * pa = &a;
//    B b, & rb = b, * pb = &b;
//    C c, & rc = c, * pc = &c;
//    A* p;
//        a.display();    // A::display()
//        b.display();   //   B::display()
//        c.display();   //   C::display()
//        ra.display();  //   A::display()
//        rb.display();  //   B::display()
//        rc.display();  //   C::display()
//        pa->display(); //  A::display()
//        pb->display();  // B::display()
//        pc->display();  //  C::display()
//        p = &a;
//    p->display();  //   A::display()
//        p = &b;
//    p->display();   //  B::display()
//        p = &c;
//    p->display();  //   C::display()
//}

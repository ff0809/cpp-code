//#include <iostream>  
//using namespace std;
//class A {
//public:
//    virtual void display() {
//        cout << "A::display()" << endl;
//    }
//};
//class B :public A {
//public:
//    void display() {
//        cout << "B::display()" << endl;
//    }
//};
//class C :public B {
//public:
//    void display() {
//        cout << "C::display()" << endl;
//    }
//};
////A类不加 virtual 的执行结果 
//int main()
//{
//    A a, & ra = a, * pa = &a;
//    B b, & rb = b, * pb = &b;
//    C c, & rc = c, * pc = &c;
//    A* p;
//    a.display();//  A::
//    b.display();  //B::
//    c.display(); // C::
//    ra.display();// A::
//    rb.display();//B::
//    rc.display(); //C::
//    pa->display();// A::
//    pb->display(); //B::
//    pc->display();// C::
//    p = &a;
//    p->display(); // A::
//    p = &b;
//    p->display();  //A::
//    p = &c;
//    p->display();  //A::
//}

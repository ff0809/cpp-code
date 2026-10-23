//#include <iostream>  
//using namespace std;
//
//class Base {
//public:
//    Base() {}
//    virtual ~Base() { cout << "Base destructor is called!" << endl; } //普通析构函数 
//};
//class Subclass :public Base {
//private: int* ptr;
//public:
//    Subclass() { ptr = new int; }
//    ~Subclass() {
//        cout << "Subclass destructor is called!" << endl; delete ptr;
//    }
//};
//int main() {
//    Subclass* a = new Subclass;  //基类指针方式
//    delete a;      //Base析构
//    return 0;      //ptr分配的内存没有得到释放
//}

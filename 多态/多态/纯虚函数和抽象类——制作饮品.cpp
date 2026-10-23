//#include<iostream>
//using namespace std;
//
//class Abstractdrinking
//{
//public:
//	virtual void a() = 0;
//	virtual void b() = 0;
//	virtual void c() = 0;
//	virtual void d() = 0;
//	void makedrink()
//	{
//		a();
//		b();
//		c();
//		d();
//	}
//};
//class coffee :public Abstractdrinking
//{
//	virtual void a()
//	{
//		cout << "a" << endl;
//	}
//	virtual void b()
//	{
//		cout << "b" << endl;
//	}
//	virtual void c()
//	{
//		cout << "c" << endl;
//	}
//	virtual void d()
//	{
//		cout << "d" << endl;
//	}
//};
//void dowork(Abstractdrinking* abs)
//{
//	abs->makedrink();
//	delete abs;
//}
//void dowork1(Abstractdrinking&abs)
//{
//	abs.makedrink();
//}
//void test()
//{
//	coffee cof;
//	dowork(new coffee);////父类传指针给子类对象（Abstractdrinking* abs=new coffee)
//	dowork1(cof);//父类传引用给子类对象（Abstractdrinking&abs=cof)
//}
//int main()
//{
//	test();
//}
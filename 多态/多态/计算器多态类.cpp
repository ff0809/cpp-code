//#include<iostream>
//using namespace std;
//
//class Abstract
//{
//public:
//	int num1=0, num2=0;
//	virtual int getres()
//	{
//		return 0;
//	}
//};
//class add:public Abstract
//{
//public:
//	int getres()
//	{
//		return num1 + num2;
//	}
//};
//class jian:public Abstract
//{
//public:
//	int getres()
//	{
//		return num1 - num2;
//	}
//};
//class cheng :public Abstract
//{
//public:
//	int getres()
//	{
//		return num1 * num2;
//	}
//};
//void calc()
//{
//	Abstract* abstract = new add;
//	abstract->num1 = 10;
//	abstract->num2 = 10;
//	cout << abstract->num1 << "+" << abstract->num2 << "=" << abstract->getres() << endl;
//	delete abstract;
//
//	abstract = new jian;
//	abstract->num1 = 10;
//	abstract->num2 = 10;
//	cout << abstract->num1 << "-" << abstract->num2 << "=" << abstract->getres() << endl;
//	delete abstract;
//
//	abstract = new cheng;
//	abstract->num1 = 10;
//	abstract->num2 = 10;
//	cout << abstract->num1 << "*" << abstract->num2 << "=" << abstract->getres() << endl;
//}
//int main()
//{
//	calc();
//}

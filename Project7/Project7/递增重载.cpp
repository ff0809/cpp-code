//#include<iostream>
//using namespace std;
//
//class integer
//{
//private:
//	int m_num;
//public:
//	friend ostream& operator<<(ostream& out, const integer &myint);
//	integer() :m_num(0) {};
//	integer& operator++()//前置递增
//	{
//		m_num++;
//		return *this;//返回引用
//	}
//	integer operator++(int)//后置递增
//	{
//		integer temp = *this;
//		m_num++;
//		return temp;//返回局部对象
//	}
//};
//ostream& operator<<(ostream& out, const integer &myint)//输出运算符（左移运算符）
//{
//	out << myint.m_num;
//	return out;
//}
//void test1()
//{
//	integer myint;
//	cout << myint++ << endl;//0
//	cout << myint << endl;//1
//}
//void test2()
//{
//	integer myint;
//	cout << ++(++myint) << endl;//2
//	cout << myint << endl;//2（若前面改为integer operator++（）则输出1）
//}
//int main()
//{
//	test1();
//	test2();
//}
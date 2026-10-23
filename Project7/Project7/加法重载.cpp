//#include<iostream>
//using namespace std;
//
//class people
//{
//public:
//	int m_a=0, m_b=0;
//	people(int a, int b) :m_a(a), m_b(b) {};
//	people operator+(const people& p)
//	{
//		people temp(0,0);
//		temp.m_a = this->m_a + p.m_a;
//		temp.m_b = this->m_b + p.m_b;
//		return temp;
//	}
//};
//void test()
//{
//	people p1(10, 10);
//	people p2(12, 23);
//	people p3 = p1 + p2;
//	cout << p3.m_a << p3.m_b << endl;
//
//}
//int main()
//{
//	test();
//}
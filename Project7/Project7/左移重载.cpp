//#include<iostream>
//using namespace std;
//
//class person
//{
//private:
//	int m_a, m_b;
//public:
//	person(int a, int b) :m_a(a), m_b(b) {};
//	friend ostream& operator<<(ostream& out, person& p);
//};
//ostream& operator<<(ostream& out, person& p)
//{
//	cout << "m_a=" << p.m_a << " m_b=" << p.m_b<<endl;
//	return out;
//}
//void test()
//{
//	person p(10, 10);
//	cout << p << "helloworld" << endl;
//}
//int main()
//{
//	test();
//}
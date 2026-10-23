//#include<iostream>
//#include<set>
//#include<string>
//using namespace std;
//
//class person
//{
//public:
//	string m_name;
//	int m_age;
//	person(string name, int age) :m_name(name), m_age(age) {};
//};
//class mycompare1
//{
//public:
//	bool operator()(const person& p1, const person& p2)const//注意一定要加const（set,map等有序容器）
//	{
//		return p1.m_age > p2.m_age;
//	}
//};
//class mycompare2
//{
//public:
//	bool operator()(int age1,int age2)const//注意一定要加const（set,map等有序容器）
//	{
//		return age1 > age2;
//	}
//};
//void test1()
//{
//	set<person, mycompare1> s;
//	person p1("xgbs", 20);
//	person p2("bhd", 26);
//	person p3("hs", 69);
//	s.insert(p1);
//	s.insert(p2);
//	s.insert(p3);
//	for (set<person, mycompare1>::iterator it = s.begin(); it != s.end(); it++)
//	{
//		cout << it->m_name << " " << it->m_age << endl;
//	}
//}
//
//void test2()
//{
//	set<int, mycompare2>s;
//	s.insert(10);
//	s.insert(30);
//	s.insert(20);
//	for (set<int, mycompare2>::iterator it = s.begin(); it != s.end(); it++)
//	{
//		cout << *it << " ";
//	}
//	cout << endl;
//}
//
//int main()
//{
//	test1();
//	test2();
//}
//

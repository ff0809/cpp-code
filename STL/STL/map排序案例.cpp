//#include<iostream>
//#include<string>
//#include<map>
//using namespace std;
//
//class person
//{
//public:
//	string m_name;
//	int m_age;
//	person(string name, int age) :m_name(name), m_age(age) {};
//};
//
//class mycompare1
//{
//public:
//	bool operator()(int v1, int v2)const
//	{
//		return v1 > v2;
//	}
//};
//
//class mycompare2
//{
//public:
//	bool operator()(const person& p1, const person& p2)const
//	{
//		return p1.m_age > p2.m_age;
//	}
//};
//
//void test1()
//{
//	map<int, int, mycompare1>m;
//	m.insert(make_pair(1, 10));
//	m.insert(make_pair(2, 20));
//	m.insert(make_pair(3, 50));
//	for(map<int,int,mycompare1>::iterator it=m.begin();it!=m.end();it++)
//	{
//		cout << it->first << " " << it->second << endl;
//	}
//	cout << endl;
//}
//
//void test2()
//{
//	map<person, person, mycompare2>m;
//	person p1("cub", 12);
//	person p2("xhbs", 13);
//	person p3("jxbs", 25);
//	m.insert(make_pair(p1, p2));
//	m.insert(make_pair(p3, p1));
//	m.insert(make_pair(p2, p3));
//	for (map<person, person, mycompare2>::iterator it = m.begin(); it != m.end(); it++)
//	{
//		cout << it->first.m_name << " " << it->first.m_age << " " << it->second.m_name << " " << it->second.m_age << endl;
//	}
//}
//
//int main()
//{
//	test1();
//	test2();
//}
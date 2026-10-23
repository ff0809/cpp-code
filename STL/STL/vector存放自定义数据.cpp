//#include<iostream>
//#include<vector>
//#include<algorithm>
//using namespace std;
//
//class person
//{
//public:
//	string m_name;
//	int m_age;
//	person(string name, int age) :m_name(name), m_age(age) {}
//};
//
//void myprint1(const person& p) // 修改为接受const引用
//{
//	cout << p.m_name << " " << p.m_age << endl;
//}
//void myprint2(const person* p)
//{
//	cout << p->m_name << " " << p->m_age << endl;
//}
//void test1()
//{
//	vector<person> v1;
//	person p1("aa", 10);
//	person p2("bb", 20);
//	v1.push_back(p1);
//	v1.push_back(p2);
//	for (vector<person>::iterator it = v1.begin(); it != v1.end(); it++)
//	{
//		cout << it->m_name << " " << it->m_age << endl;
//	}
//	for_each(v1.begin(), v1.end(), myprint1); // 现在可以正常调用
//}
//void test2()
//{
//	vector<person*>v2;
//	person p1("aa", 10);
//	person p2("bb", 20);
//	v2.push_back(&p1);
//	v2.push_back(&p2);
//	for (vector<person*>::iterator it = v2.begin(); it != v2.end(); it++)
//	{
//		cout << (*it)->m_name << " " << (*it)->m_age << endl;
//	}
//	for_each(v2.begin(), v2.end(), myprint2);
//}
//int main()
//{
//	test1();
//	test2();
//}
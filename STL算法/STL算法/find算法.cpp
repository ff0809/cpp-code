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
//	person(string name, int age) :m_name(name), m_age(age) {};
//
//	bool operator==(const person& p)//非常重要的重载函数，因为编译器本身不认识自定义类型的==
//	{
//		if (p.m_name == m_name && p.m_age == m_age)
//		{
//			return true;
//		}
//		return false;
//	}
//};
//void test1()
//{
//	vector<int>v1;
//	for (int i = 0; i < 10; i++)
//	{
//		v1.push_back(i);
//	}
//	vector<int>::iterator it=find(v1.begin(), v1.end(), 5);
//	if (it == v1.end())
//	{
//		cout << "未找到" << endl;
//	}
//	else
//	{
//		cout << "找到" << *it << endl;
//	}
//}
//
//void test2()
//{
//	vector<person>v2;
//	person p1("n", 12);
//	person p2("hcc", 125);
//	person p3("cnd", 25);
//	person p("n", 12);
//	v2.push_back(p1);
//	v2.push_back(p2);
//	v2.push_back(p3);
//	vector<person>::iterator it = find(v2.begin(), v2.end(), p);
//	if (it == v2.end())
//	{
//		cout << "未找到" << endl;
//	}
//	else
//	{
//		cout << "找到" << it->m_name << " " << it->m_age << endl;
//	}
//}
//
//int main()
//{
//	test1();
//	test2();
//}
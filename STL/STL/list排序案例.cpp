//#include<iostream>
//#include<string>
//#include<list>
//using namespace std;
//
//class person
//{
//public:
//	string m_name;
//	int m_age;
//	int m_height;
//	person(string name, int age, int height)
//	{
//		m_name = name;
//		m_age = age;
//		m_height = height;
//	}
//};
//bool compare(person& p1, person& p2)
//{
//	if (p1.m_age == p2.m_age)
//	{
//		return p1.m_height > p2.m_height;
//	}
//	return p1.m_age < p2.m_age;
//}
//
//list<person>l;
//void mysort()
//{
//	person p1("chdb", 12, 155);
//	person p2("dh", 13, 156);
//	person p3("cud", 12, 169);
//	l.push_back(p1);
//	l.push_back(p2);
//	l.push_back(p3);
//	l.sort(compare);
//}
//void printinfo()
//{
//	for (list<person>::iterator it = l.begin(); it != l.end(); it++)
//	{
//		cout << it->m_name << " " << it->m_age << " " << it->m_height << endl;
//	}
//}
//int main()
//{
//	mysort();
//	printinfo();
//}
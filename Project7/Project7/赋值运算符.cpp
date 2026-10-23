//#include<iostream>
//using namespace std;
//
//class person
//{
//public:
//	int* m_age;
//	person(int age) 
//	{
//		m_age = new int(age);
//	}
//    person& operator=(person& p)
//    {
//        if (m_age != null)
//        {
//            delete m_age;
//            m_age = null;
//        }
//        m_age = new int(*p.m_age); // 修正：应从p.m_age深拷贝而不是自身
//        return *this;
//    }
//};
//void test()
//{
//	person p1(18);
//	person p2(20);
//	person p3(30);
//	p3 = p2 = p1;
//	cout << *p1.m_age << *p2.m_age << *p3.m_age << endl;
//}
//int main()
//{
//	test();
//}
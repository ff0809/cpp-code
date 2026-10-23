//#include<iostream>
//using namespace std;
//
//class building;
//class good
//{
//private:
//	building* m_building;
//public:
//	void visit1();
//	void visit2();
//	good();
//};
//class building
//{
//private:
//	string m_bedroom;
//public:
//	friend void good::visit1();
//	string m_livingroom;
//	building();
//
//};
//building::building()
//{
//	m_livingroom = "客厅";
//	m_bedroom = "卧室";
//}
//good::good()
//{
//	m_building = new building;
//}
//void good::visit1()
//{
//	cout << "访问" <<m_building->m_livingroom << endl;
//	cout << "访问" << m_building->m_bedroom << endl;
//}
//void good::visit2()
//{
//	cout << "访问" << m_building->m_livingroom << endl;
//}
//void test()
//{
//	good go;
//	go.visit1();
//	go.visit2();
//}
//int main()
//{
//	test();
//}
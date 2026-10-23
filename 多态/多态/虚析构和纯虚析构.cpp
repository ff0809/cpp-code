//#include<iostream>
//using namespace std;
//
//class Animal
//{
//public:
//	Animal()
//	{
//		cout << "Animal构造函数调用" << endl;
//	}
//	virtual void speak() = 0;
//	virtual~Animal() = 0;
//};
//Animal::~Animal()
//{
//	cout << "Animal虚析构函数调用" << endl;
//}
//class cat :public Animal
//{
//public:
//	string *m_name;
//	cat(string name)
//	{
//		cout << "cat构造函数调用" << endl;
//		m_name = new string(name);
//	}
//	virtual void speak()
//	{
//		cout << *m_name<<"猫说话" << endl;
//	}
//	~cat()
//	{
//		cout << "cat析构函数调用" << endl;
//		if (this->m_name != NULL)
//		{
//			delete m_name;
//			m_name = NULL;
//		}
//	}
//};
//void test()
//{
//	Animal* animal = new cat("Tom");
//	animal->speak();
//	delete animal;
//}
//int main()
//{
//	test();
//}
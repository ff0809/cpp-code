//#include<iostream>
//using namespace std;
//#include<vector>
//
//void printinfo(vector<int>& v)
//{
//	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
//	{
//		cout << *it << " ";
//	}
//	cout << endl;
//}
//void test1()
//{
//	vector<int>v1;
//	for (int i = 0; i < 10; i++)
//	{
//		v1.push_back(i);
//	}
//	cout << v1.capacity() << " " << v1.size() << endl;
//	printinfo(v1);
//	vector<int>v2;
//	for (int i = 10; i > 0; i--)
//	{
//		v2.push_back(i);
//	}
//	printinfo(v2);
//	v1.swap(v2);
//	cout << v2.capacity() << " " << v2.size() << endl;
//	printinfo(v1);
//	printinfo(v2);
//}
//void test2()
//{
//	vector<int>v;
//	for (int i = 0; i < 10000; i++)
//	{
//		v.push_back(i);
//	}
//	cout << v.capacity() << " " << v.size() << endl;
//
//	v.resize(3);
//	//vector<int>(v).swap(v);//匿名对象，所有版本都可使用
//	v.shrink_to_fit();//C++11以上可以用，该版本可以使用
//	cout << v.capacity() << " " << v.size() << endl;
//}
//
//int main()
//{
//	test1();
//	test2();
//}
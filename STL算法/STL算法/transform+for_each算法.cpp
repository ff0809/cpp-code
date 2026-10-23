//#include<iostream>
//#include<vector>
//#include<algorithm>
//using namespace std;
//
//class Transform
//{
//public:
//	int operator()(int v)
//	{
//		return v + 100;
//	}
//};
//class myprint
//{
//public:
//	void operator()(int v)
//	{
//		cout << v <<" ";
//	}
//
//};
//
//void test()
//{
//	vector<int>v;
//	for (int i = 0; i < 10; i++)
//	{
//		v.push_back(i);
//	}
//	vector<int>v1;
//	v1.resize(v.size());
//	transform(v.begin(), v.end(), v1.begin(), Transform());
//	for_each(v1.begin(), v1.end(), myprint());
//}
//int main()
//{
//	test();
//}
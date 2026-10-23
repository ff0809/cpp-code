//#include<iostream>
//#include<vector>
//#include<algorithm>
//using namespace std;
//
//void myprint(int val)
//{
//	cout << val << endl;
//}
//
//void test()
//{
//	vector<int>v;
//	v.push_back(10); v.push_back(20); v.push_back(30); v.push_back(40);
//	//第一种
//	vector<int>::iterator pbegin = v.begin();
//	vector<int>::iterator pend = v.end();
//	while (pbegin != pend)
//	{
//		cout << *pbegin << endl;
//		pbegin++;
//	}
//	//第二种
//	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
//	{
//		cout << *it << endl;
//	}
//	//第三种
//	for_each(v.begin(), v.end(), myprint);
//}
//int main()
//{
//	test();
//}
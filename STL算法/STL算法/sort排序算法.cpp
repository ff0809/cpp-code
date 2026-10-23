#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void myprint(int v)
{
	cout << v << endl;
}
void test()
{
	vector<int>v;
	v.push_back(10);
	v.push_back(30);
	v.push_back(20);
	sort(v.begin(), v.end());
	for_each(v.begin(), v.end(), myprint);
	sort(v.begin(), v.end(), greater<int>());
	for_each(v.begin(), v.end(), myprint);
}
int main()
{
	test();
}
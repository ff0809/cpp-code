#include<iostream>
using namespace std;
int main1()
{
	long long year;
	long long second;
	cout << "请输入年数：" << endl;
	cin >> year;
	second = year * 365 * 24 * 60 * 60;
	cout << year << "年一共" << second << "秒。" << endl;

	return 0;
}
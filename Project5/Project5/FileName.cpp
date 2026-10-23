#include<iostream>
using namespace std;
int main()
{
	int gram, jin, liang, qian;
	cout << "请输入质量（g):" << endl;
	cin >> gram;
	cout << gram / 500 << "斤" << gram % 500 / 50 << "两" << gram % 500 % 50 / 5 << "钱" << endl;



	return 0;
}
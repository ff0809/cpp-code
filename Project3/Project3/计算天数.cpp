#include<iostream>
using namespace std;


int myfunction()
{
	int N1, N2, N;     //N1和N2分别表示出生年和当前年，N表示天数
	cin >> N1 >> N2;
	N = (N2 - N1) * 365;
	cout << "一共" << N << "天。" << endl;

	return 0;
}
int main()
{
	myfunction();

	return 0;
}
#include<iostream>
using namespace std;

int main()
{
	int N1, N2, N3;
	cout << "请输入三个整数(第一个为十进制，第二个为八进制，第三个为十六进制）：" << endl;
	cin >> dec >> N1;
	cin >> oct >> N2;
	cin >> hex >> N3;

	cout <<"N1的十进制，八进制，十六进制形式分别为："<< dec << N1 << " " << oct << N1 << " " << hex << N1 << endl;
	cout <<"N2的十进制，八进制，十六进制形式分别为："<< dec << N2 << " " << oct << N2 << " " << hex << N2 << endl;
	cout <<"N3的十进制，八进制，十六进制形式分别为："<< dec << N3 << " " << oct << N3 << " " << hex << N3 << endl;

	return 0;
}
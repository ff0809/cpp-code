#include<iostream>
using namespace std;

void itobs(int num, char* buffer)
{
	int pos = 0;
	for (int i = 31; i >= 0; i--)
	{
		int bit = (num >> i) & 1;
		buffer[pos++] = bit ? '1' : '0';
		if (i % 8 == 0 && i != 0)
		{
			buffer[pos++] = ' ';
		}
	}
	buffer[pos] = '\0';
	cout << num << "的二进制是：" << buffer << endl;
}

int main()
{
	cout << "输入一些整数：" << endl;
	int num;
	char buffer[100];
	while (true)
	{
		if (cin >> num)
		{
			itobs(num, buffer);
		}
		else
		{
			cout << "------程序结束------" << endl;
			break;
		}
	}
	return 0;
}
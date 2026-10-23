#include "swap1.h"//分文件编写源文件也应加上头文件！！！

//函数的定义
void swap1(int m, int n)
{
	int temp = m;
	m = n;
	n = temp;
	cout << "调换后：" << endl;
	cout << "m=" << m << endl;
	cout << "n=" << n << endl;
}
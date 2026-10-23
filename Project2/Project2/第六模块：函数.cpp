#include<iostream>
using namespace std;
#include"swap1.h"//分文件编写主函数一定要加上头文件！！！

/*
1.函数定义：返回类型 函数名（参数列表（也称为形参列表，即没有真实数据的参数））{函数体语句 return表达式}
2.函数调用：当调用函数时，调用时候的值为实际参数，会将其传递给形参进行运算再将结果赋值到下面的调用函数中
总结：函数定义小括号里面的参数为形参，函数调用时传入的参数为实参
3.函数值传递：传递过程中形参会改变，但不会影响实参的值!!!
4.函数样式：①无参无返（void 函数名()）；②有参无返（void函数名(int a));③无参有返（int函数名（） return整型；④有参有返（int函数名（int a) return整型   有参或有反时可能换数据类型！
5.函数声明：提前告诉编译器函数的存在，避免报错（将自定义函数写到主函数后面实一定要写函数声明！在主函数前面可不写。声明可以有多次（一次即可），定义只能有一次，声明方式为定义方式加分号
6.函数的分文件编写：创建一个头文件（.h)和一个源文件（.cpp),在头文件中写函数声明并在源文件中写函数定义，
注：①注意源文件和最后主函数所在的源文件必须包含头文件（用双引号包含表示自定义）
    ②头文件中应该包含主函数所在文件前两行否则无法运行！！！

*/
int add(int num1, int num2)//定义加法函数
{
	int sum = num1 + num2;
	return sum;
}
void swap(int num3, int num4)//void空函数不用写返回值！！！
{
	cout << "交换前：" << endl;
	cout << "num3=" << num3 << endl;
	cout << "num4=" << num4 << endl;

	int temp = num3;
	num3 = num4;
	num4 = temp;
	cout << "交换后：" << endl;
	cout << "num3=" << num3 << endl;
	cout << "num4=" << num4 << endl;


}
//无参无返
void test1()//空类型不可以创建变量
{
	cout << "This is test1" << endl;
}
//有参无返
void test2(int a)
{
	a = 100;
	cout << "a=" << a << endl;
}
//无参有返
int test3()
{
	return 10;
}
//有参有返
int test4(int a)
{
	a = 100;
	return a;
}

int max(int x, int y);//函数声明，使max函数定义可以写到主函数下方

int main6666()
{
	int a = 10;
	int b = 20;

	int c = add(a, b);
	cout << "c=" << c << endl;
	
	swap(a, b);
	cout << "main中的a=" << a << endl;
	cout << "main中的b=" << b << endl;

	test1();
	test2(a);
	int e = test3();
	cout << "e=" <<e<< endl;
	int d=test4(a);
	cout << "d=" << d << endl;
	
	int x = 30;
	int y = 40;
	max(x, y);
	
	int m = 200;
	int n = 100;
	swap1(m, n);
	return 0;
}

int max(int x, int y)//上方声明了函数于是定义可以写在main函数下方
{
	if (x > y)
	{
		cout << x << endl;
	}
	else
	{
		cout << y << endl;
	}
	return 0;
}
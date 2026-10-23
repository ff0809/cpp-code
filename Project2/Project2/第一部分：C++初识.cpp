#include<iostream>
using namespace std;

/*常量的定义方式
1.#define 宏常量，定义在函数上方
2.const修饰的变量，定义在函数下方

不要用关键字给变量或常量起名称
标识符不能用关键字，只能用字母数字下划线，且第一个字符只能是字母或下划线，区分大小写，建议见名知义
*/
//上述符号为多行注释
#define Day 7//宏常量的定义方式：#define 宏常量名 宏常量值
const int month=12; //const修饰的变量的定义方式：const 变量类型 变量名=变量初始值

int main44()
{
	int a = 1314520;//变量创建的语法：变量类型 变量名 = 变量初始值
	cout << "a=" << a << endl;
    cout << "hello world" << endl; //输出Hello world

	cout << "一周总共有：" << Day << "天" << endl;
	cout << "一周总共有：" << month << "个月" << endl;

	system("pause");

	return 0;
}
#include<iostream>
using namespace std;

class Myprint
{
public:
	void operator()(string name)
	{
		cout << name << endl;
	}
};

class Myadd
{
public:
	int operator()(int m, int n)
	{
		return m + n;
	}
};
void test1()
{
	Myprint myprint;
	myprint("·Ñ·²");
}
void test2()
{
	Myadd myadd;
	int ret = myadd(10, 10);
	cout << ret << endl;
	cout << Myadd()(100, 100) << endl;

}
int main()
{
	test1();
	test2();
}
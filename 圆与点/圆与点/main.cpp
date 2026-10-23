#include<iostream>
using namespace std;
#include"circle.h"
#include"point.h"

int main()
{
	circle c;
	point p;
	c.set(10, 0, 0);
	p.set(3, 4);
	if ((c.getx() - p.getx()) * (c.getx() - p.getx()) + (c.gety() - p.gety()) * (c.gety() - p.gety()) < c.getr() * c.getr())
	{
		cout << "点在圆内" << endl;
	}
	else if (((c.getx() - p.getx()) * (c.getx() - p.getx()) + (c.gety() - p.gety()) * (c.gety() - p.gety()) == c.getr() * c.getr()))
	{
		cout << "点在圆上" << endl;
	}
	else
	{
		cout << "点在圆外" << endl;
	}
}
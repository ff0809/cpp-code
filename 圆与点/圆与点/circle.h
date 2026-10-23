#pragma once
#include<iostream>
using namespace std;

class circle
{
private:
	int mr, mx, my;
public:
	void set(int r, int x, int y);
	int getr();
	int getx();
	int gety();
};

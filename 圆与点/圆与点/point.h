#pragma once
#include<iostream>
using namespace std;

class point
{
private:
	int mx, my;
public:
	void set(int x, int y);
	int getx();
	int gety();
};
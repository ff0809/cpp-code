#pragma once
#include<iostream>
using namespace std;

class identity
{
public:
	virtual void opermenu() = 0;//操作菜单的纯虚函数，子类后续重写
	string m_name;
	string m_code;
};
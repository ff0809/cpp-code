#pragma once
#include<iostream>
#include<map>
#include"file.h"
#include<fstream>
using namespace std;

class orderfile
{
public:
	 orderfile();
	 void updateorder();
	 int m_size=0;//预约记录数
	 map<int, map<string, string>> m_orderdata;//预约记录容器，key为日期，value为时间段和预约状态
};
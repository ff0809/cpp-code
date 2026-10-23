#pragma once
#include<iostream>
#include"identity.h"
#include"orderfile.h"
#include<vector>
using namespace std;

class teacher :public identity
{
public:
	int m_id;
	teacher();
	teacher(int id, string name, string code);
	virtual void opermenu();
	void showall();
	void valid();
};
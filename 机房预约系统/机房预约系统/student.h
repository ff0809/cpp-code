#pragma once
#include<iostream>
#include"identity.h"
#include"file.h"
#include<fstream>
using namespace std;

class student :public identity
{
public:
	int m_id;
	student();
	student(int id, string name, string code);
	virtual void opermenu();
	void applyorder();
	void showmy();
	void showall();
	void cancel();
};
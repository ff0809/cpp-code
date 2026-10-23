#pragma once
#include <iostream>
using namespace std;
#include"worker.h"

class Workermanager
{
public:
	Workermanager();

	int m_num;
	worker** m_array;
	bool isempty;

	void showmenu();
	void exitSystem();
	void add();
	void save();
	int getnum();
	void init();
	void show();
	int isexist(int id);
	int isexist2(string name);
	void del();
	void mod();
	void find();
	void sort();
	void clean();

	~Workermanager();
};

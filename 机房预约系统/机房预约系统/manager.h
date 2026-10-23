#include<iostream>
#include"identity.h"
#include<vector>
#include"student.h"
#include"teacher.h"
#include"computer.h"
#include<string>
#include<fstream>
#include"file.h"
using namespace std;

class manager :public identity
{
public:
	vector<student>vs;
	vector<teacher>vt;
	vector<computer>vc;
	bool check(int id, int type);
	
	manager();
	manager(string name, string code);
	virtual void opermenu();
	void add();
	void showperson();
	void showcomputer();
	void clean();
	void init();
	void initcomputer();

};
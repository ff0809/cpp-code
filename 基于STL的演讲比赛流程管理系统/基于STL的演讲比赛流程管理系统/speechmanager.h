#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<deque>
#include<algorithm>
#include<functional>
#include<numeric>
#include<fstream>
#include<string>
#include<ctime>
#include"speaker.h"

using namespace std;

class speechmanager
{
public:
	speechmanager();

	vector<int>v1;
	vector<int>v2;
	vector<int>v3;
	map<int, speaker>m;
	int m_index;
	bool isempty;
	map<int, vector<string>>m_record;

	void menu();
	void exitsystem();
	void init();
	void create();
	void begin();
	void choose();
	void contest();
	void showresult();
	void save();
	void load();
	void find();
	void clear();
	
	~speechmanager();
};
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<ctime>
using namespace std;
#define ce 0
#define mei 1
#define yan 2

class person
{
public:
	string m_name;
	int m_money;
	person(string name, int money) :m_name(name), m_money(money){};
};

void add(vector<person>& v)
{
	string seed = "ABCDEFGHIJ";
	int money = 0;
	for (int i = 0; i < 10; i++)
	{
		string name = "员工";
		name += seed[i];
		money = rand() % 10000 + 10000;
		person p(name, money);
		v.push_back(p);
	}
}

void set(vector<person>&v,multimap<int,person>&m)
{
	for (vector<person>::iterator it = v.begin(); it != v.end(); it++)
	{
		int num = rand() % 3;
		m.insert(make_pair(num, *it));
	}
}

void show(multimap<int, person>& m)
{
	multimap<int, person>::iterator pos = m.find(ce);
	cout << "策划：" << endl;
	while(pos!=m.end()&&pos->first==ce)
	{
		cout << (*pos).second.m_name << " " << pos->second.m_money << endl;
		pos++;
	}
	pos = m.find(mei);
	cout << "美术：" << endl;
	while (pos != m.end() && pos->first == mei)
	{
		cout << (*pos).second.m_name << " " << pos->second.m_money << endl;
		pos++;
	}
	pos = m.find(yan);
	cout << "研究：" << endl;
	while (pos != m.end() && pos->first == yan)
	{
		cout << (*pos).second.m_name << " " << pos->second.m_money << endl;
		pos++;
	}
}

int main()
{
	srand((unsigned int)time(NULL));
	vector<person>v;
	multimap<int, person>m;
	add(v);
	set(v, m);
	show(m);
}
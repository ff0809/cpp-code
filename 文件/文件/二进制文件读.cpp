#include<iostream>
using namespace std;
#include<fstream>
#include<string>

class person
{
public:
	string m_name;
	int m_id=0;
};

void test()
{
	ifstream ifs("text1.txt", ios::in | ios::binary);
	if (!ifs.is_open())
	{
		cout << "文件打开失败" << endl;
		return;
	}
	person p;
	ifs.read((char*)&p, sizeof(p));
	cout << "姓名：" << p.m_name << " 学号：" << p.m_id << endl;
}

int main()
{
	test();
}
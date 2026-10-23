#include"workermanager.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
#include<fstream>
Workermanager::Workermanager()
{
	ifstream ifs;
	ifs.open("information.txt", ios::in);
	if (!ifs.is_open())
	{
		/*cout << "文件不存在" << endl;*/
		m_num = 0;
		m_array = NULL;
		isempty = true;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		/*cout << "文件为空" << endl;*/
		m_num = 0;
		m_array = NULL;
		isempty = true;
		ifs.close();
		return;
	}
	int num = getnum();
	m_num = num;
	m_array = new worker * [m_num];
	init();
}
void Workermanager::showmenu()
{
	cout << "**********************************" << endl;
	cout << "********** 职工管理系统 **********" << endl;
	cout << "********** 1.添加职工 **********" << endl;
	cout << "********** 2.显示职工 **********" << endl;
	cout << "********** 3.删除职工 **********" << endl;
	cout << "********** 4.修改职工 **********" << endl;
	cout << "********** 5.查找职工 **********" << endl;
	cout << "********** 6.排序职工 **********" << endl;
	cout << "********** 7.清空内容 **********" << endl;
	cout << "********** 0.退出系统 **********" << endl;
	cout << "**********************************" << endl;
}
void Workermanager::exitSystem()
{
	cout << "欢迎下次使用！" << endl;
	exit(0);
}
void Workermanager::add()
{
	cout << "请输入添加的员工数量" << endl;
	int add_num;
	cin >> add_num;
	if (add_num > 0)
	{
		int new_num = add_num + m_num;
		worker** newspace = new worker * [new_num];
		if (m_array != NULL)
		{
			for (int i = 0; i < m_num; i++)
			{
				newspace[i] = m_array[i];
			}
		}
		for (int i = 0; i < add_num; i++)
		{
			int id;
			string name;
			int select;
			cout << "请输入第" << i + 1 << "位员工的编号：" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "位员工的姓名：" << endl;
			cin >> name;
			cout << "请输入第" << i + 1 << "位员工的职位：" << endl;
			cout << "1代表普通员工，2代表经理，3代表老板" << endl;
			cin >> select;
			worker* worker = NULL;
			switch (select)
			{
			case 1:
				worker = new employee(id, name, 1);
				break;
			case 2:
				worker = new manager(id, name, 2);
				break;
			case 3:
				worker = new boss(id, name, 3);
				break;
			default:
				break;
			}
			newspace[m_num + i] = worker;
		}
		delete[] m_array;
		m_array = newspace;
		m_num = new_num;
		cout << "成功添加" << add_num << "位新员工！" << endl;
		isempty = false;
		save();
	}
	else
	{
		cout << "输入错误" << endl;
	}
	system("pause");
	system("cls");
}
void Workermanager::save()
{
	ofstream ofs;
	ofs.open("information.txt", ios::out);
	for (int i = 0; i < m_num; i++)
	{
		ofs << m_array[i]->m_id << " " << m_array[i]->m_name << " " << m_array[i]->m_did << endl;
	}
	ofs.close();
}
int Workermanager::getnum()
{
	ifstream ifs;
	ifs.open("information.txt", ios::in);
	int id;
	string name;
	int did;
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		num++;
	}
	ifs.close();
	return num;
}
void Workermanager::init()
{
	ifstream ifs;
	ifs.open("information.txt", ios::in);
	int id;
	string name;
	int did;
	int idx = 0;
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		worker* worker = NULL;
		if (did == 1)
		{
			worker = new employee(id, name, 1);
		}
		else if (did == 2)
		{
			worker = new manager(id, name, 2);
		}
		else
		{
			worker = new boss(id, name, 3);
		}
		m_array[idx] = worker;
		idx++;
	}
	ifs.close();
}
void Workermanager::show()
{
	if (isempty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		for (int i = 0; i < m_num; i++)
		{
			m_array[i]->showinfo();
		}
	}
	system("pause");
	system("cls");
}
int Workermanager::isexist(int id)
{
	int index = -1;
	for (int i = 0; i < m_num; i++)
	{
		if (m_array[i]->m_id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}
int Workermanager::isexist2(string name)
{
	int index = -1;
	for (int i = 0; i < m_num; i++)
	{
		if (m_array[i]->m_name == name)
		{
			index = i;
			break;
		}
	}
	return index;
}
void Workermanager::del()
{
	if (isempty)
	{
		cout << "文件不存在或文件为空" << endl;
	}
	else
	{
		cout << "请输入想删除的职工编号" << endl;
		int id;
		cin >> id;
		if (isexist(id) == -1)
		{
			cout << "查无此人，删除失败" << endl;
		}
		else
		{
			delete m_array[isexist(id)];
			for (int i = isexist(id); i < m_num-1; i++)
			{
				m_array[i] = m_array[i + 1];
			}
			m_array[m_num - 1] = NULL;
			m_num--;
			cout << "删除成功" << endl;
			save();
		}
	}
	system("pause");
	system("cls");
}
void Workermanager::mod()
{
	if (isempty)
	{
		cout << "文件不存在或为空" << endl;
	}
	else
	{
		cout << "请输入想删除的职工编号" << endl;
		int id;
		cin >> id;
		int index = isexist(id);
		if (index == -1)
		{
			cout << "修改失败，查无此人" << endl;
		}
		else
		{
			delete m_array[index];
			cout << "请输入新的职工编号：" << endl;
			cin >> id;
			cout << "请输入新的职工姓名：" << endl;
			string name;
			cin >> name;
			cout << "请输入新的职工职位（1代表普通员工，2代表经理，3代表老板）：" << endl;
			int newselect;
			cin >> newselect;
			worker* worker = NULL;
			switch (newselect)
			{
			case 1:
				worker = new employee(id, name, 1);
				break;
			case 2:
				worker = new manager(id, name, 2);
				break;
			case 3:
				worker = new boss(id, name, 3);
				break;
			}
			m_array[index] = worker;
			cout << "修改成功" << endl;
			save();
		}
	}
	system("pause");
	system("cls");
}
void Workermanager::find()
{
	if (isempty)
	{
		cout << "文件不存在或为空" << endl;
	}
	else
	{
		cout << "请输入查找方式：（1按照编号，2按照姓名）" << endl;
		int select;
		cin >> select;
		if (select == 1)
		{
			cout << "请输入想查找的职工编号" << endl;
			int id;
			cin >> id;
			int index = isexist(id);
			if (index == -1)
			{
				cout << "查找失败，查无此人" << endl;
			}
			else
			{
				cout << "查找成功" << endl;
				m_array[index]->showinfo();
			}
		}
		else if (select == 2)
		{
			cout << "请输入想查找的职工姓名" << endl;
			string name;
			cin >> name;
			int index = isexist2(name);
			if (index == -1)
			{
				cout << "查找失败，查无此人" << endl;
			}
			else
			{
				cout << "查找成功" << endl;
				m_array[index]->showinfo();
			}
		}
		else
		{
			cout << "输入无效,请重新输入" << endl;
			find();
		}
	}
	system("pause");
	system("cls");
}
void Workermanager::sort()
{
	if (isempty)
	{
		cout << "文件不存在或为空" << endl;
	}
	else
	{
		cout << "请选择排序方式：（1为按照员工编号升序排列，2为降序）" << endl;
		int choice;
		cin >> choice;
		if (choice == 1)
		{
			for (int i = 0; i < m_num - 1; i++)
			{
				for (int j = 0; j < m_num - i - 1; j++)
				{
					if (m_array[j]->m_id > m_array[j + 1]->m_id)
					{
						worker* temp = m_array[j];
						m_array[j] = m_array[j + 1];
						m_array[j + 1] = temp;
					}
				}
			}
			cout << "排序成功,排序后的结果为：" << endl;
			save();
			show();
		}
		else if (choice == 2)
		{
			for (int i = 0; i < m_num - 1; i++)
			{
				for (int j = 0; j < m_num - i - 1; j++)
				{
					if (m_array[j]->m_id < m_array[j + 1]->m_id)
					{
						worker* temp = m_array[j];
						m_array[j] = m_array[j + 1];
						m_array[j + 1] = temp;
					}
				}
			}
			cout << "排序成功,排序后的结果为：" << endl;
			save();
			show();
		}
	}
	system("pause");
	system("cls");
}
void Workermanager::clean()
{
	cout << "确认清空吗（y/n)？" << endl;
	char c;
	cin >> c;
	if (c == 'y'||'Y')
	{
		ofstream ofs;
		ofs.open("information.txt", ios::trunc);
		if (m_array != NULL)
		{
			for (int i = 0; i < m_num; i++)
			{
				delete m_array[i];
				m_array[i] = NULL;
			}
			m_num = 0;
			delete[]m_array;
			m_array = NULL;
			isempty = true;
		}
	}
	else
	{
	}
	system("pause");
	system("cls");
}

Workermanager::~Workermanager()
{
	if (m_array != NULL)
	{
		for (int i = 0; i < m_num; i++)
		{
			delete m_array[i];
			m_array[i] = NULL;
		}
		delete[]m_array;
		m_array = NULL;
	}
}
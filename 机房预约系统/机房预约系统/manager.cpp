#include"manager.h"

manager::manager()
{

}

manager::manager(string name, string code)
{
	m_name = name;
	m_code = code;
	init();
	initcomputer();
}

void manager::opermenu()
{
	cout << "欢迎管理员：" << m_name << "登录！" << endl;
	cout << "\t\t---------------------------------\n" << endl;
	cout << "\t\t|                               |\n" << endl;
	cout << "\t\t|          1.添加账号           |\n" << endl;
	cout << "\t\t|                               |\n" << endl;
	cout << "\t\t|          2.查看账号           |\n" << endl;
	cout << "\t\t|                               |\n" << endl;
	cout << "\t\t|          3.查看机房           |\n" << endl;
	cout << "\t\t|                               |\n" << endl;
	cout << "\t\t|          4.清空预约           |\n" << endl;
	cout << "\t\t|                               |\n" << endl;
	cout << "\t\t|          0.退出登录           |\n" << endl;
	cout << "\t\t---------------------------------\n" << endl;
	cout << "请选择您的操作：" << endl;
}

void manager::init()
{
	vs.clear();
	vt.clear();
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件不存在！" << endl;
		return;
	}
	student s;
	int id;
	string name;
	string code;
	while (ifs >> id && ifs >> name && ifs >> code)
	{
		s = student(id, name, code);
		vs.push_back(s);
	}
	ifs.close();
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件不存在！" << endl;
		return;
	}
	teacher t;
	while (ifs >> id && ifs >> name && ifs >> code)
	{
		t = teacher(id, name, code);
		vt.push_back(t);
	}
	ifs.close();
	cout << "学生人数：" << vs.size() << endl;
	cout << "教师人数：" << vt.size() << endl;
}

void manager::add()
{
	ofstream ofs;
	int id = 0;
	string name;
	string code;
	string filename;
	cout << "请输入添加账号的类型（1.学生 2.教师）" << endl;
	int select = 0;
	cin >> select;
	if(select == 1)
	{
		filename = STUDENT_FILE;
		cout << "请输入学号：" << endl;
		cin >> id;
		if (check(id, 1))
		{
			cout << "学号已存在，请重新添加！" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
	else
	{
		filename = TEACHER_FILE;
		cout << "请输入职工号：" << endl;
		cin >> id;
		if(check(id, 2))
		{
			cout << "职工号已存在，请重新添加！" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
	cout << "请输入姓名：" << endl;
	cin >> name;
	cout << "请输入密码：" << endl;
	cin >> code;
	ofs.open(filename, ios::out | ios::app);
	ofs << id << " " << name << " " << code << endl;
	cout << "添加成功！" << endl;
	ofs.close();
	init();
	system("pause");
	system("cls");
}

bool manager::check(int id, int type)
{
	if (type == 1)
	{
		for (vector<student>::iterator it = vs.begin(); it != vs.end(); it++)
		{
			if (it->m_id == id)
			{
				return true;
			}
		}
		return false;
	}
	else
	{
		for (vector<teacher>::iterator it = vt.begin(); it != vt.end(); it++)
		{
			if (it->m_id == id)
			{
				return true;
			}
		}
		return false;
	}
}

void manager::showperson()
{
	cout << "请选择查看类型（1.学生 2.教师）" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		if (vs.size() == 0)
		{
			cout << "当前无学生信息！" << endl;
			return;
		}
		for (vector<student>::iterator it = vs.begin(); it != vs.end(); it++)
		{
			cout << "学号：" << it->m_id << "\t姓名：" << it->m_name << "\t密码：" << it->m_code << endl;
		}
	}
	else
	{
		if (vt.size() == 0)
		{
			cout << "当前无教师信息！" << endl;
			return;
		}
		for (vector<teacher>::iterator it = vt.begin(); it != vt.end(); it++)
		{
			cout << "职工号：" << it->m_id << "\t姓名：" << it->m_name << "\t密码：" << it->m_code << endl;
		}
	}
	system("pause");
	system("cls");
}

void manager::initcomputer()
{
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件不存在！" << endl;
		return;
	}
	computer c;
	while (ifs >> c.c_id >> c.c_maxnum)
	{
		vc.push_back(c);
	}
	ifs.close();
}

void manager::showcomputer()
{
	for(vector<computer>::iterator it=vc.begin();it!=vc.end();it++)
	{
		cout << "机房编号：" << it->c_id << "\t机房容量：" << it->c_maxnum << endl;
	}
	system("pause");
	system("cls");
}

void manager::clean()
{
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::trunc);
	ofs.close();
	cout << "清空成功！" << endl;
	system("pause");
	system("cls");
}


#include"teacher.h"

teacher::teacher() :m_id(0) {}

teacher::teacher(int id, string name, string code)
{
	m_id = id;
	m_name = name;
	m_code = code;
}
void teacher::opermenu()
{
	cout << "欢迎教师：" << m_name << "登录！" << endl;
	cout << "\t\t---------------------------------\n" << endl;
	cout << "\t\t|                               |\n" << endl;
	cout << "\t\t|        1.查看所有预约         |\n" << endl;
	cout << "\t\t|                               |\n" << endl;
	cout << "\t\t|        2.审核预约申请         |\n" << endl;
	cout << "\t\t|                               |\n" << endl;
	cout << "\t\t|        0.退出登录             |\n" << endl;
	cout << "\t\t---------------------------------\n" << endl;
	cout << "请选择您的操作：" << endl;
}
void teacher::showall()
{
	orderfile of; // 读取预约文件数据
	if (of.m_size == 0)
	{
		cout << "当前无任何预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}
	// 遍历所有预约记录，直接显示（不筛选学号）
	for (int i = 0; i < of.m_size; i++)
	{
		cout << i + 1 << ". ";
		cout << "日期：周" << of.m_orderdata[i]["日期"] << "\t";
		cout << "时间段：" << of.m_orderdata[i]["时间段"] << "\t";
		cout << "机房编号：" << of.m_orderdata[i]["机房编号"] << "\t";
		cout << "学生学号：" << of.m_orderdata[i]["学生学号"] << "\t";
		cout << "学生姓名：" << of.m_orderdata[i]["学生姓名"] << "\t";
		cout << "审核状态：";
		if (of.m_orderdata[i]["审核状态"] == "1") cout << "审核中" << endl;
		else if (of.m_orderdata[i]["审核状态"] == "2") cout << "预约成功" << endl;
		else if (of.m_orderdata[i]["审核状态"] == "-1") cout << "审核未通过" << endl;
		else cout << "预约已取消" << endl;
	}
	system("pause");
	system("cls");
}
void teacher::valid()
{
	orderfile of;
	if (of.m_size == 0)
	{
		cout << "当前无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}
	int index = 1;
	vector<int>v;
	for (int i = 0; i < of.m_size; i++)
	{
		if (of.m_orderdata[i]["审核状态"] == "1")
		{
			cout << index++ << ". ";
			cout << "日期：周" << of.m_orderdata[i]["日期"] << "\t";
			cout << "时间段：" << (of.m_orderdata[i]["时间段"] == "1" ? "上午" : "下午") << "\t";
			cout << "机房编号：" << of.m_orderdata[i]["机房编号"] << "\t";
			cout << "学生学号：" << of.m_orderdata[i]["学生学号"] << "\t";
			cout << "学生姓名：" << of.m_orderdata[i]["学生姓名"] << "\t";
			cout << "审核状态：审核中" << endl;
			v.push_back(i);
		}
	}
	if (v.size() == 0)
	{
		cout << "当前无待审核预约！" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "请输入需要审核的预约记录编号（0表示返回）：" << endl;
	int select = 0;
	cin >> select;
	if (select < 0 || select > v.size())
	{
		cout << "输入有误，请重新输入！" << endl;
		system("pause");
		system("cls");
		return;
	}
	else if (select == 0)
	{
		return;
	}
	else
	{
		cout << "请输入审核结果（1.通过 2.不通过）：" << endl;
		int res = 0;
		cin >> res;
		if (res == 1)
		{
			of.m_orderdata[v[select - 1]]["审核状态"] = "2";
		}
		else if (res == 2)
		{
			of.m_orderdata[v[select - 1]]["审核状态"] = "-1";
		}
		else
		{
			cout << "输入有误，返回上一级！" << endl;
			system("pause");
			system("cls");
			return;
		}
		of.updateorder();
		cout << "审核完毕！" << endl;
		system("pause");
		system("cls");
	}
}

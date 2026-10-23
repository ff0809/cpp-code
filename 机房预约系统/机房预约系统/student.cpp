#include"student.h"
#include"manager.h"
#include"orderfile.h"

student::student():m_id(0){}

student::student(int id, string name, string code)
{
	m_id = id;
	m_name = name;
	m_code = code;
}
void student::opermenu()
{
	cout << "欢迎学生代表："<<m_name<<"登录！"<<endl;
	cout << "\t\t---------------------------------\n" << endl;
	cout << "\t\t|                               |\n" << endl;
	cout << "\t\t|        1.申请预约机房         |\n" << endl;
	cout << "\t\t|                               |\n" << endl;
	cout << "\t\t|        2.查看我的预约         |\n" << endl;
	cout << "\t\t|                               |\n" << endl;
	cout << "\t\t|        3.查看所有预约         |\n" << endl;
	cout << "\t\t|                               |\n" << endl;
	cout << "\t\t|        4.取消预约申请         |\n" << endl;
	cout << "\t\t|                               |\n" << endl;
	cout << "\t\t|        0.退出登录             |\n" << endl;
	cout << "\t\t---------------------------------\n" << endl;
	cout << "请选择您的操作：" << endl;
}
void student::applyorder()
{
	cout << "机房开发时间为周一至周五" << endl;
	cout << "请输入申请预约的时间：" << endl;
	cout << "1.周一" << endl;
	cout << "2.周二" << endl;
	cout << "3.周三" << endl;
	cout << "4.周四" << endl;
	cout << "5.周五" << endl;
	int date = 0;
	cin >> date;
	if (date < 1 || date>5)
	{
		cout << "输入有误，请重新输入！" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "请输入申请预约的时间段：" << endl;
	cout << "1.上午" << endl;
	cout << "2.下午" << endl;
	int time = 0;
	cin >> time;
	if (time < 1 || time>2)
	{
		cout << "输入有误，请重新输入！" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "请输入申请预约的机房编号：" << endl;
	cout << "1号机房（容量20人）" << endl;
	cout << "2号机房（容量50人）" << endl;
	cout << "3号机房（容量100人）" << endl;
	int c_id = 0;
	int state = 1;
	cin >> c_id;
	if (c_id < 1 || c_id>3)
	{
		cout << "输入有误，请重新输入！" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "预约申请成功，等待审核！" << endl;
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);
	ofs << "日期:" << date << "\t时间段:" << time << "\t机房编号:" << c_id << "\t学生学号:" << m_id << "\t学生姓名:" << m_name << "\t审核状态:" << state<<endl;
	ofs.close();
	system("pause");
	system("cls");
}
void student::showmy()
{
	orderfile of;
	if (of.m_size == 0)
	{
		cout << "当前无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}
	bool flag = false;
	for (int i = 0; i < of.m_size; i++)
	{
		if (atoi(of.m_orderdata[i]["学生学号"].c_str()) == m_id)
		{
			cout << "预约日期：周" << of.m_orderdata[i]["日期"] << "\t";
			cout << "时间段：" << (of.m_orderdata[i]["时间段"]=="1"?"上午" : "下午") << "\t";
			cout << "机房编号：" << of.m_orderdata[i]["机房编号"] << "\t";
			cout << "审核状态：";
			if (of.m_orderdata[i]["审核状态"] == "1") cout << "审核中" << endl;
			else if (of.m_orderdata[i]["审核状态"] == "2") cout << "预约成功" << endl;
			else if (of.m_orderdata[i]["审核状态"] == "-1") cout << "审核未通过" << endl;
			else cout << "预约已取消" << endl;
		}
	}
	system("pause");
	system("cls");
}
void student::showall()
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
void student::cancel()
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
		if (of.m_orderdata[i]["学生学号"] == to_string(m_id) && (of.m_orderdata[i]["审核状态"] == "1" || of.m_orderdata[i]["审核状态"] == "2"))
		{
			v.push_back(i);
			cout << index++ << "、";
			cout << "日期：周" << of.m_orderdata[i]["日期"] << "\t";
			cout << "时间段：" << (of.m_orderdata[i]["时间段"] == "1" ? "上午" : "下午") << "\t";
			cout << "机房编号：" << of.m_orderdata[i]["机房编号"] << "\t";
			cout << "审核状态：";
			if (of.m_orderdata[i]["审核状态"] == "1") cout << "审核中" << endl;
			else if (of.m_orderdata[i]["审核状态"] == "2") cout << "预约成功" << endl;
		}
	}
	cout << "请输入取消预约的记录编号（按0可返回上一级）：" << endl;
	int select = 0;
	cin >> select;
	if (select < 0 || select>v.size())
	{
		cout << "输入有误，请重新输入！" << endl;
		system("pause");
		system("cls");
		return;
	}
	else if(select == 0)
	{
		system("cls");
		return;
	}
	else
	{
		of.m_orderdata[v[select - 1]]["审核状态"] = "0";
		of.updateorder();
		cout << "已成功取消预约！" << endl;
		system("pause");
		system("cls");
		return;
	}
}
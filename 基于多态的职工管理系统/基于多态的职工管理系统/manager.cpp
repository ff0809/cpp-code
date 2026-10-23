#include"manager.h"

manager::manager(int id, string name, int did)
{
	m_id = id;
	m_name = name;
	m_did = did;
}
void manager::showinfo()
{
	cout << "职工编号：" << m_id
		<< "\t职工姓名：" << m_name
		<< "\t岗位：" << dname()
		<< "\t岗位职责：完成老板交给的任务，并下发任务给员工"
		<< endl;
}
string manager::dname()
{
	return "经理";
}
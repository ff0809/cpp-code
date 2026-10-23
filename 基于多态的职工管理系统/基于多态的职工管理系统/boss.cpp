#include"boss.h"

boss::boss(int id, string name, int did)
{
	m_id = id;
	m_name = name;
	m_did = did;
}
void boss::showinfo()
{
	cout << "职工编号：" << m_id
		<< "\t职工姓名：" << m_name
		<< "\t岗位：" << dname()
		<< "\t岗位职责：管理公司所有事务"
		<< endl;
}
string boss::dname()
{
	return "老板";
}
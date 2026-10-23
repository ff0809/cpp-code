#include"employee.h"

employee::employee(int id, string name, int did)
{
	m_id = id;
	m_name = name; 
	m_did = did;
}
void employee::showinfo()
{
	cout<<"职工编号："<<m_id
		<<"\t职工姓名："<<m_name
		<<"\t岗位："<<dname()
		<<"\t岗位职责：完成经理交给的任务"
		<< endl;
}
string employee::dname()
{
	return "普通员工";
}
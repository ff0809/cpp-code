#include<iostream>
using namespace std;
#define Max 1000

struct people
{
	string name;
	int sex;
	int age;
	string phone;
	string address;
};
struct tongxun
{
	int size=0;
	people p[Max] = {};
};

void menu()
{
	cout << "**************************" << endl;
	cout << "*****1.添加联系人*******" << endl;
	cout << "*****2.显示联系人*******" << endl;
	cout << "*****3.删除联系人*******" << endl;
	cout << "*****4.查找联系人*******" << endl;
	cout << "*****5.修改联系人*******" << endl;
	cout << "*****6.清空联系人*******" << endl;
	cout << "*****0.退出通讯录*******" << endl;
	cout << "**************************" << endl;
}
void add(tongxun* q)
{
	if(q->size >= Max)
	{
		cout << "通讯录已满，无法添加新联系人！" << endl;
		system("pause"); // 暂停，等待用户按键
		system("cls"); // 清屏
	}
	cout << "请输入姓名：" << endl;
	cin >> q->p[q->size].name;
	cout << "请输入性别：" << endl;
	cin >> q->p[q->size].sex;
	cout << "请输入年龄：" << endl;
	cin >> q->p[q->size].age;
	cout << "请输入电话：" << endl;
	cin >> q->p[q->size].phone;
	cout << "请输入地址：" << endl;
	cin >> q->p[q->size].address;
	q->size++;
	system("pause"); // 暂停，等待用户按键
	system("cls"); // 清屏
}
void show(tongxun*q)
{
	for (int i = 0; i < q->size; i++)
	{
		cout << "姓名：" << q->p[i].name;
		cout << "\t性别：" << (q->p[i].sex == 1 ? "男" : "女");
		cout << "\t年龄：" << q->p[i].age;
		cout << "\t电话：" << q->p[i].phone;
		cout << "\t地址：" << q->p[i].address << endl;
	}
	system("pause"); // 暂停，等待用户按键
	system("cls"); // 清屏
}
void del(tongxun*q)
{
	cout << "请输入要删除的联系人姓名：" << endl;
	string name;
	cin >> name;
	bool found = false;
	for (int i = 0; i < q->size; i++)
	{
		if (q->p[i].name == name)
		{
			found = true;
			for(int j=i;j < q->size - 1; j++)
			{
				q->p[j] = q->p[j + 1]; // 将后面的元素前移
			}
			q->size--; // 减少通讯录大小
			break; // 找到后退出循环
		}
	}
	if (not found)
	{
		cout << "查无此人！" << endl;
	}
	else
	{
		cout << "删除成功！" << endl;
	}
	system("pause"); // 暂停，等待用户按键
	system("cls"); // 清屏
}
void find(tongxun*q)
{
	cout << "请输入要查找的联系人姓名：" << endl;
	string name;
	cin >> name;
	bool found = false;
	for (int i = 0; i < q->size; i++)
	{
		if (q->p[i].name == name)
		{
			found = true;
			cout << "姓名：" << q->p[i].name;
			cout << "\t性别：" << (q->p[i].sex == 1 ? "男" : "女");
			cout << "\t年龄：" << q->p[i].age;
			cout << "\t电话：" << q->p[i].phone;
			cout << "\t地址：" << q->p[i].address << endl;
		}
	}
	if (not found)
	{
		cout << "查无此人！" << endl;
	}
	system("pause"); // 暂停，等待用户按键
	system("cls"); // 清屏
}
void modify(tongxun*q)
{
	cout << "请输入要修改的联系人姓名：" << endl;
	string name;
	cin >> name;
	bool found = false;
	for (int i = 0; i < q->size; i++)
	{
		if (q->p[i].name == name)
		{
			found = true;
			cout << "请输入新的姓名：" << endl;
			cin >> q->p[i].name;
			cout << "请输入新的性别：" << endl;
			cin >> q->p[i].sex;
			cout << "请输入新的年龄：" << endl;
			cin >> q->p[i].age;
			cout << "请输入新的电话：" << endl;
			cin >> q->p[i].phone;
			cout << "请输入新的地址：" << endl;
			cin >> q->p[i].address;
		}
	}
	if(not found)
	{
		cout << "查无此人！" << endl;
	}
	else
	{
		cout << "修改成功！" << endl;
	}
	system("pause"); // 暂停，等待用户按键
	system("cls"); // 清屏
}
void clean(tongxun*q)
{
	cout << "确定要清空通讯录吗？(y/n)" << endl;
	char a;
	cin >> a;
	if (a == 'y' || a == 'Y')
	{
		q->size = 0; // 清空通讯录
		cout << "通讯录已清空！" << endl;
	}
	else
	{
		cout << "操作取消！" << endl;
	}
	system("pause"); // 暂停，等待用户按键
	system("cls"); // 清屏
}
void exit()
{
	cout << "确定要退出通讯录系统吗？(y/n)" << endl;
	char a;
	cin >> a;
	if (a == 'y' || a == 'Y')
	{
		cout << "感谢使用通讯录系统，再见！" << endl;
		exit(0); // 退出程序
	}
	else
	{
		cout << "操作取消，继续使用通讯录系统！" << endl;
		system("pause"); // 暂停，等待用户按键
		system("cls"); // 清屏
	}
}
int main() 
{
	tongxun p;// 初始化通讯录
	while(true)
	{
		menu();
		int select = 0;
		cin >> select;
		switch (select)
		{
		case 1:
			add(&p);
			break;
		case 2:
			show(&p);
			break;
		case 3:
			del(&p);
			break;
		case 4:
			find(&p);
			break;
		case 5:
			modify(&p);
			break;
		case 6:
			clean(&p);
			break;
		case 0:
			exit();
			break;
		}
	}
	return 0;
}
#include<iostream>
#include<fstream>
#include"file.h"
#include"identity.h"
#include"student.h"
#include"teacher.h"
#include"manager.h"
using namespace std;

// 管理员菜单
void managerMenu(identity*& mgr)
{
    while (true)
    {
        // 显示管理员菜单
        mgr->opermenu();

        // 强制类型转换为 manager*，因为identity类没有manager类里面的部分函数
        manager* man = (manager*)mgr;
        int select = 0;
        cout << "请输入操作选项：" << endl;
        cin >> select;

        if (select == 1) // 添加账号
        {
            cout << "添加账号" << endl;
            man->add();
        }
        else if (select == 2) // 查看账号
        {
            cout << "查看账号" << endl;
            man->showperson();
        }
        else if (select == 3) // 查看机房
        {
            cout << "查看机房" << endl;
            man->showcomputer();
        }
        else if (select == 4) // 清空预约
        {
            cout << "清空预约" << endl;
            man->clean();
        }
        else if (select == 0) // 退出
        {
            cout << "注销成功" << endl;
            system("pause");
            system("cls");
            return;
        }
        else
        {
            cout << "输入有误，请重新输入！" << endl;
            system("pause");
            system("cls");
        }
    }
}

void studentMenu(identity*& stud)
{
    while (true)
    {
		stud->opermenu();
        student* stu = (student*)stud;
		int select = 0;
		cout << "请输入操作选项：" << endl;
		cin >> select;
        if (select == 1) // 申请预约机房
        {
			stu->applyorder();
        }
        else if (select == 2) // 查看我的预约
		{
			stu->showmy();
        }
        else if (select == 3) // 查看所有预约
        {
            stu->showall();
        }
        else if (select == 4) // 取消预约申请
        {
			stu->cancel();
        }
        else if (select == 0) // 退出
        {
            cout << "注销成功" << endl;
            system("pause");
            system("cls");
            return;
        }
        else
        {
            cout << "输入有误，请重新输入！" << endl;
            system("pause");
            system("cls");
		}
    }
}

void teacherMenu(identity*& teach)
{
    while (true)
    {
        // 显示教师菜单
        teach->opermenu();
        // 强制类型转换为 teacher*，因为identity类没有teacher类里面的部分函数
        teacher* tea = (teacher*)teach;
        int select = 0;
        cout << "请输入操作选项：" << endl;
        cin >> select;
        if (select == 1) // 查看所有预约
        {
            cout << "查看所有预约" << endl;
            tea->showall();
        }
        else if (select == 2) // 审核预约
        {
            cout << "审核预约" << endl;
            tea->valid();
        }
        else if (select == 0) // 退出
        {
            cout << "注销成功" << endl;
            system("pause");
            system("cls");
            return;
        }
        else
        {
            cout << "输入有误，请重新输入！" << endl;
            system("pause");
            system("cls");
        }
    }
}

void login(string filename, int type)
{
    identity* person = NULL;
    ifstream ifs(filename, ios::in);
    if (!ifs.is_open())
    {
        cout << "文件不存在！" << endl;
        return;
    }

    int id = 0;
    string name, code;
    if (type == 1)
    {
        cout << "请输入学号：" << endl;
        cin >> id;
    }
    else if (type == 2)
    {
        cout << "请输入职工号：" << endl;
        cin >> id;
    }
    cout << "请输入姓名：" << endl;
    cin >> name;
    cout << "请输入密码：" << endl;
    cin >> code;

    if (type == 1)
    {
        int fid;
        string fname, fcode;
        while (ifs >> fid >> fname >> fcode)
        {
            if (fid == id && fname == name && fcode == code)
            {
                cout << "学生登录验证成功！" << endl;
                system("pause");
                system("cls");
                person = new student(id, name, code);
				studentMenu(person);
				return;
            }
        }
    }
    else if (type == 2)
    {
        int fid;
        string fname, fcode;
        while (ifs >> fid >> fname >> fcode)
        {
            if (fid == id && fname == name && fcode == code)
            {
                cout << "教师登录验证成功！" << endl;
                system("pause");
                system("cls");
                person = new teacher(id, name, code);
				teacherMenu(person);
                return;
            }
        }
    }
    else if (type == 3)
    {
        string fname, fcode;
        while (ifs >> fname >> fcode)
        {
            if (fname == name && fcode == code)
            {
                cout << "管理员身份验证成功！" << endl;
                system("pause");
                system("cls");
                person = new manager(name, code);
                managerMenu(person);
                return;
            }
        }
    }
    cout << "验证失败！" << endl;
    system("pause");
    system("cls");
    return;
}

int main()
{
    int choice = 0;
    while (true)
    {
        cout << "----------------欢迎使用机房预约系统----------------" << endl;
        cout << "请输入您的身份" << endl;
        cout << "\t\t--------------------------------\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          1.学生代表           |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          2.老师               |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          3.管理员             |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          0.退出系统           |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t--------------------------------\n";
        cout << endl;
        cout << "请输入您的选择：" << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            login(STUDENT_FILE, 1);
            break;
        case 2:
            login(TEACHER_FILE, 2);
            break;
        case 3:
            login(ADMIN_FILE, 3);
            break;
        case 0:
            cout << "欢迎下次使用！" << endl;
            system("pause");
            return 0;
        default:
            cout << "输入有误，请重新输入" << endl;
            system("pause");
            system("cls");
            continue;
        }
    }
    return 0;
}

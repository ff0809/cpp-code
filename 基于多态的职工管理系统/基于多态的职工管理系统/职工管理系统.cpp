#include<iostream>
using namespace std;
#include"workermanager.h"

int main()
{
	Workermanager wm;
	int choice = 0;
	while(true)
	{
		wm.showmenu();
		cout << "请输入您的选择：";
		cin >> choice;
		switch(choice)
		{
			case 1:
				wm.add();
				break;
			case 2:
				wm.show();
				break;
			case 3:
				wm.del();
				break;
			case 4:
				wm.mod();
				break;
			case 5:
				wm.find();
				break;
			case 6:
				wm.sort();
				break;
			case 7:
				wm.clean();
				break;
			case 0:
				wm.exitSystem();
			default:
				cout << "输入错误，请重新输入！" << endl;
				system("pause");
				system("cls");
				break;
		}
	}
}
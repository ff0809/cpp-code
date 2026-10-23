#include<iostream>
#include"speechmanager.h"
using namespace std;

int main()
{
	srand((unsigned int)time(NULL));
	speechmanager sm;
	int choice = 0;
	while (true)
	{
		sm.menu();
		cout << "ÇëÊäÈëÄãµÄÑ¡Ôñ£º" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			sm.begin();
			break;
		case 2:
			sm.find();
			break;
		case 3:
			sm.clear();
			break;
		case 0:
			sm.exitsystem();
			break;
		default:
			system("cls");
			break;
		}
	}
}
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

void wait_for_enter();
void print_menu();
void print_help();
void print_exit();
void print_interface(int board[4][4], int score, int step);
void play_game();
//其实这个项目书写的本质，就是判断上下左右移动时有没有空格可以补位和有没有数字进行合并的操作，若两者均没有则不可进行移动
void moveup(int board[4][4], int& score, int& step)
{
	for (int j = 0; j < 4; j++)
	{
		int temp = 0;
		int last = -1; // 记录上一个合并的位置，防止同一格多次合并
		for (int i = 0; i < 4; i++)
		{
			if (board[i][j] != 0)
			{
				if (temp > 0 && board[temp - 1][j] == board[i][j] && last != temp - 1)//合并操作
				{
					board[temp - 1][j] *= 2;
					score += board[temp - 1][j];
					board[i][j] = 0;
					last = temp - 1;
				}
				else
				{
					if (i != temp)//补空格操作
					{
						board[temp][j] = board[i][j];
						board[i][j] = 0;
					}
					temp++;
				}
			}
		}
	}
}
void movedown(int board[4][4], int& score, int& step)
{
	for (int j = 0; j < 4; j++)
	{
		int temp = 3;
		int last = -1;
		for (int i = 3; i >= 0; i--)
		{
			if (board[i][j] != 0)
			{
				if (temp < 3 && board[temp + 1][j] == board[i][j] && last != temp + 1)
				{
					board[temp + 1][j] *= 2;
					score += board[temp + 1][j];
					board[i][j] = 0;
					last = temp + 1;
				}
				else
				{
					if (i != temp)
					{
						board[temp][j] = board[i][j];
						board[i][j] = 0;
					}
					temp--;
				}
			}
		}
	}
}
void moveleft(int board[4][4], int& score, int& step)
{
	for (int i = 0; i < 4; i++)
	{
		int temp = 0;
		int last = -1;
		for (int j = 0; j < 4; j++)
		{
			if (board[i][j] != 0)
			{
				if (temp > 0 && board[i][temp - 1] == board[i][j] && last != temp - 1)
				{
					board[i][temp - 1] *= 2;
					score += board[i][temp - 1];
					board[i][j] = 0;
					last = temp - 1;
				}
				else
				{
					if (j != temp)
					{
						board[i][temp] = board[i][j];
						board[i][j] = 0;
					}
					temp++;
				}
			}
		}
	}
}
void moveright(int board[4][4], int& score, int& step)
{
	for (int i = 0; i < 4; i++)
	{
		int temp = 3;
		int last = -1;
		for (int j = 3; j >= 0; j--)
		{
			if (board[i][j] != 0)
			{
				if (temp < 3 && board[i][temp + 1] == board[i][j] && last != temp + 1)
				{
					board[i][temp + 1] *= 2;
					score += board[i][temp + 1];
					board[i][j] = 0;
					last = temp + 1;
				}
				else
				{
					if (j != temp)
					{
						board[i][temp] = board[i][j];
						board[i][j] = 0;
					}
					temp--;
				}
			}
		}
	}
}
void random1(int board[4][4])// 游戏初始化，包括生成随机数等操作（初始生成2个数字）
{  
   int num = 0;  
   if (rand() % 10 != 0) // 90%概率生成2,10%概率生成4  
       num = 2;  
   else  
       num = 4;  
   for (int i = 0; i < 2; ++i)  
   {  
       int x = rand() % 4;  
       int y = rand() % 4;  
       if (board[x][y] == 0)  
           board[x][y] = num;  
       else  
           --i; // 如果该位置已经有数字，则重新生成  
   }  
}
void random2(int board[4][4])//后续操作过程中生成随机数（每次移动后生成一个数字）
{
	int num = 0;
	if (rand() % 10 != 0) // 90%概率生成2,10%概率生成4
		num = 2;
	else
		num = 4;
	for (int i = 0; i < 1; ++i)
	{
		int x = rand() % 4;
		int y = rand() % 4;
		if (board[x][y] == 0)
			board[x][y] = num;
		else
			--i; // 如果该位置已经有数字，则重新生成
	}
}
bool can_move(int board[4][4]) // 判断盘面是否可以继续移动
{
	// 有空格就能移动
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			if (board[i][j] == 0)
				return true;
	// 检查相邻是否有相同，有相同可以进行合并，也可以移动
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j) 
		{
			if (i < 3 && board[i][j] == board[i + 1][j])
				return true;
			if (j < 3 && board[i][j] == board[i][j + 1]) 
				return true;
		}
	return false;// 如果没有空格且相邻没有相同的数字，则不能继续移动
}
bool is_board_changed(int old_board[4][4], int board[4][4])//判断棋盘是否发生变化（即是否进行了无效的上下左右操作而无法进行移动）
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			if (board[i][j] != old_board[i][j])
				return true;
	return false;
}
bool has_2048(int board[4][4])
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			if (board[i][j] ==2048)
				return true;
	return false;
}
void play_game()
{
	// 变量声明
	int board[4][4] = {}; // 4*4的棋盘
	int score = 0;		  // 分数
	int step = 0;		  // 步数
	char choice = '\0';	  // 用户选择
	bool already_win = false; // 是否已经获得2048的布尔值检验（开始我并未进行这个设置，在测试时考虑到后续点Y后仍会反复出现这个提示，因此设置了这个变量，避免重复提示）

	// 游戏初始化，包括生成随机数等操作
	random1(board); // 初始化棋盘

	// 打印游戏界面
	print_interface(board, score, step);

	while (1)
	{
		// 获取用户输入
		choice = _getch();

		int old_board[4][4]; // 记录上一步棋盘状态
		memcpy(old_board, board, sizeof(board)); // 复制当前棋盘状态
		bool changed = false; // 标记棋盘是否发生变化

		// 根据用户输入进行相应操作
		switch (choice)
		{
		case 27: // ESC键退出
			print_exit();
			return;
		case 72: // 上
			moveup(board, score, step);
			changed = is_board_changed(old_board,board); // 检查棋盘是否发生变化
			break;
		case 80: // 下
			movedown(board, score, step);
			changed = is_board_changed(old_board, board); 
			break;
		case 75: // 左
			moveleft(board, score, step);
			changed = is_board_changed(old_board, board); 
			break;
		case 77: // 右
			moveright(board, score, step);
			changed = is_board_changed(old_board, board); 
			break;
		default:
			continue; // 如果输入不合法，则继续等待输入
		}
		if (changed)//满足移动后盘面会发生改变才会进行下面的操作，规避了步数错误增加等问题
		{
			random2(board);
			step++; 
			print_interface(board, score, step); 
			// 给出到达2048的提示让用户判断是否继续游戏
			if (has_2048(board)&&!already_win)
			{
				already_win = true; // 设置为已经获得2048,之后不再提示
				cout << "恭喜你获得2048，游戏胜利！是否继续游戏？" << endl;
				cout << "按Y继续游戏，按N退出游戏" << endl;//此时若输入N或n则退出游戏,若输入Y或y则继续游戏，当继续进行后续移动时退出的提示将会消失
				choice = _getch();
				if (choice == 'N' || choice == 'n')
				{
					print_exit();
					return;
				}
				else
				{
					system("CLS");//清屏
					print_interface(board, score, step); // 刷新游戏界面
				}
			}
			else if (!can_move(board))//检验出无论如何都无法继续移动给出游戏结束的提示
			{
				cout << "无法继续移动！游戏结束！" << endl;
				wait_for_enter();
				return;
			}
		}
		else
		{
			print_interface(board, score, step); //当按下上下左右的其中一个无法移动且其他某方向仍可移动时不会退出，只是刷新游戏界面且步数保持不变
		}
	}
	print_exit();
}

int main()
{
	srand(static_cast<unsigned int>(time(0)));// 设置随机数种子
	char choice = '\0';
	// 设置控制台标题为2048
	SetConsoleTitle(TEXT("2048"));
	// 主循环
	while (1)
	{
		// 调用菜单显示函数
		print_menu();
		// 获取用户选择
		choice = _getche();

		// 根据用户选择进行相应操作
		switch (choice)
		{
		case 'a':
			play_game();
			break;
		case 'b':
			print_help();
			break;
		case 'c':
			print_exit();
			return 0;
		default:
			cout << "\n输入错误，请重新输入" << endl;
			wait_for_enter();
		}
	}
	return 0;
}

void wait_for_enter()
{
	cout << endl << "按回车键继续";
	while (_getch() != '\r')
		;
	cout << endl << endl;
}

void print_menu()
{
	// 清屏
	system("CLS");
	// 获取标准输出设备句柄
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN);
	// 打印菜单
	cout << "--------------------------------------------\n";
	cout << "********************************************\n";
	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	// 打印标题
	cout << "                   2048\n";
	cout << "                a.经典模式\n";
	cout << "                b.游戏规则\n";
	cout << "                c.退出游戏\n";
	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN);
	// 打印菜单
	cout << "********************************************\n";
	cout << "--------------------------------------------\n";

	// 恢复控制台文字颜色为默认颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "\n请输入你的选择(a-c):";
}

void print_help()
{
	// 清屏
	system("CLS");
	// 获取标准输出设备句柄
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN);
	cout << "--------------------------------------------\n";
	cout << "********************************************\n\n";
	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	// 打印游戏规则
	cout << "操作说明：\n\n";
	cout << "↓：下   ←：左  ↑：上  →：右  ESC键：退出\n\n";
	cout << "游戏介绍：\n\n";
	cout << "每次选择一个方向移动，移动时数字向该方向靠拢\n";
	cout << "相同数字可合并，移动后空格处会生成随机数字2/4\n";
	cout << "如果得到数字2048，则游戏胜利!\n";
	cout << "如果棋盘被数字填满，无法进行移动，则游戏失败!\n\n";
	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN);
	cout << "********************************************\n";
	cout << "--------------------------------------------\n";
	// 恢复控制台文字颜色为默认颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	wait_for_enter();
}

void print_exit()
{
	cout << "\n退出中";
	for (int i = 4; i > 0; --i)
	{
		Sleep(200);
		cout << ".";
	}
}

void print_interface(int board[4][4], int score, int step)
{
	// 清屏
	system("CLS");
	//获取标准输入设备句柄
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN);
	// 打印游戏界面
	cout << "            --------------------------------------------\n";
	cout << "            分数：" << setw(6) << score << "              步数：" << setw(6) << step << endl;
	cout << "            --------------------------------------------\n";
	cout << "            ********************************************\n";
	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "                       |----|----|----|----|\n";

	for (int i = 0; i < 4; i++)
	{
		cout << "                       |";
		for (int j = 0; j < 4; j++)
		{
			if (board[i][j] != 0)
			{
				cout << setw(4) << board[i][j] << "|";
			}
			else
			{
				cout << "    |";
			}
		}
		cout << "\n                       |----|----|----|----|\n";
	}

	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN);
	cout << "            ********************************************\n";
	cout << "            --------------------------------------------\n";
	cout << "            ↓：下   ←：左  ↑：上  →：右  ESC键：退出\n\n";

	// 恢复控制台文字颜色为默认颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}
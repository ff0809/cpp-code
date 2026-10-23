#include<iostream>
using namespace std;
#include<ctime>//使用随机数种子时需要包含此头文件！！！


int main()
{
/*
1.选择结构
①if语句：if（条件）{条件成立执行的语句}, else { 条件不满足执行的语句 } 注：if和else语句最后不能加分号！！！！，且要像函数一样前后加上大括号（否则只执行if和else后的第一条语句）！！
注：单行if语句只用if；多行if语句用if和else；多条件if语句用if，else if和else，嵌套if语句则是在某个选择条件下再加入同样的if,else if和else，书写方式都类似	
②三目运算符：（条件？条件成立执行的语句：条件不成立执行的语句）注：三目运算符返回的是一个变量，可以继续赋值给这个变量！！！事例见下方
③switch语句：switch(变量）{case 常量:(有冒号！！！）执行语句 break（退出当前分支！！！一定要加！！！）;接下来同理......   最后default（作用同前面的else):执行语句 break；}
注：switch语句中case后面的常量（必须是常量！！！）不能重复，且case后面的常量必须是整型或字符型，不能是浮点型或字符串型！！！
2.循环结构：
①while循环：while（循环条件）{循环体} 注：while后面不能加分号！！！先判断条件是否成立，再执行循环体，直到条件不成立为止，注：避免出现死循环！！！(如while（1）为死循环，因为1计算机默认为真）
②do...while循环：do{循环体}while（循环条件）；先执行循环体，再判断条件是否成立，直到不满足while里面条件为止。注：至少会执行一次循环体！！！
补充：如：int num=0，while（num），{cout<<num<<endl;num++},会输出0，因为计算机默认0为假，所以不会进行任何输出！！！///但如果采用do...while循环，则会从0开始无无限输出，因为先执行+1操作
      再看是否满足条件，此时输出为1为真，且后面皆满足while条件！！！
③for循环：for（初始条件0；循环条件1；循环表达式2）{循环体3}注：for循环中初始条件只会执行一次，即执行顺序为0132132132......
④嵌套循环：在循环体中加上循环体，外层循环1次，内层循环一周,注意换行的位置！！！
3.跳转结构：
①break语句：跳出当前循环并终止此循环，在switch条件语句中用于终止case分支并跳出switch；在循环语句中跳出当前循环语句（for while do...while);在嵌套循环中跳出最近的内层循环,事例见下方
②continue语句：结束本次循环并返回去执行上面的循环，不再执行continue后面的语句
注：与break的区别：break直接跳出整个循环，而continue只是跳出本次循环，继续执行下一次循环
③goto语句（不推荐使用，会影响逻辑结构和阅读体验）：...goto 标记：...标记：...   会直接跳过第二个省略号中包含的语句，只执行第一个和第三个省略号里面的语句

*/

	//if语句
	int score;
		cout << "请输入分数：" << endl;
		cin >> score;
		if (score > 692)
		{
			cout << "恭喜考上清北！" << endl;
			if (score > 695)
			{
				cout << "恭喜考上北大!" << endl;
			}
			else
				cout << "那你就上清华呗..." << endl;
		}
		else if(score>680)
		{
			cout << "恭喜考上科大" << endl;
		}
		else
		{
			cout << "你也很优秀哦！" << endl;
		}

		//三目运算符
		int a = 10, b = 20, d;
			int c = a > b ? a : b;
			cout << "c=" << c << endl;//此时不满足a>b这一条件,因此返回的是：后面的值(b)，若满足条件则返回？后面的值
			(a > b ? a : b) = 100;
			cout << "a=" << a << endl;//返回10，上述开始运用三目运算符得到变量是b,a并未被进行赋值，因此输出仍为10
			cout << "b=" << b << endl;//返回100，上述开始运用三目运算符得到变量是b,因此下面将b赋值为了100

			//switch语句
			int point;
			cout << "请输入分数：" << endl;
			cin >> point;
			switch (point)
			{
			case 10:
			case 9:
				cout << "非常好！" << endl;
				break;//break终止switch语句中当前的case分支
			case 8:
			case 7:
			case 6:
				cout << "很好！" << endl;
				break;
			default:
				cout << "继续加油哇！" << endl;
				break;
			}

			//while循环
			int num;
				cout << "请输入一个整数：";
				cin >> num;
				while (num<10)
				{
					cout << num << endl;
					num++;
				}
				// 案例：随机数小游戏
				srand((unsigned int)time(NULL)); // 添加随机数种子，利用当前系统时间生成随机数，防止每次生成的随机数都一样，注意要添加<ctime>头文件！！！
				int num1 = rand() % 100 + 1; // 系统随机生成0+1到99+1之间的随机数，即1到100之间的随机数
				int val;
				int attempts = 0; // 记录猜测次数
				int maxAttempts = 10; // 最大猜测次数
				int bestScore = maxAttempts + 1; // 记录最佳成绩，初始值设为最大猜测次数+1

				while (attempts < maxAttempts) // 设置循环，直到猜对或达到最大猜测次数为止
				{
					cout << "请输入你猜测的数字（剩余次数：" << maxAttempts - attempts << "）：" << endl;
					cin >> val;
					attempts++;

					if (val > num1)
					{
						cout << "猜大了" << endl;
					}
					else if (val < num1)
					{
						cout << "猜小了" << endl;
					}
					else
					{
						cout << "猜对了！" << endl;
						if (attempts < bestScore)
						{
							bestScore = attempts; // 更新最佳成绩
							cout << "恭喜你创造了新的最佳成绩！" << endl;
						}
						break; // 猜对则退出当前循环
					}
				}

				if (attempts == maxAttempts && val != num1)
				{
					cout << "很遗憾，你没有在规定次数内猜对。正确答案是：" << num1 << endl;
				}
				else
				{
					cout << "你用了 " << attempts << " 次猜对了数字。" << endl;
					if (attempts <= 3)
					{
						cout << "你真是个天才！" << endl;
					}
					else if (attempts <= 6)
					{
						cout << "你很聪明！" << endl;
					}
					else
					{
						cout << "继续加油哇！" << endl;
					}
				}

				cout << "游戏结束，感谢你的参与！" << endl;

				//do...while循环
				int num2 = 0;
				cout << "请输入整数：" << endl;
				cin >> num2;
				do
				{
					cout << num2 << endl;
					num2++;
				} 
				while (num2<10);

				//案例：水仙花数
				int num3 = 100;
				do
				{
				int x, y, z;
				x = num3 / 100;
				y = num3 / 10 % 10;
				z = num3 % 10;
				if (num3 == x * x * x + y * y * y + z * z * z)
				
					cout << num3 << "是水仙花数" << endl;
				num3++;
				}
				while (num3 < 1000);

				//for循环
				for (int i = 0; i <= 9; i++)
				{
					cout << i << endl;
					if (i== 5)
						break;//break中止for循环
				}
				
				//案例：敲桌子
				for (int num4 = 1; num4 <= 100; num4++)
				{
					if (num4 % 7 == 0 || num4 % 10 == 7 || num4 / 10 == 7)
						cout << "敲桌子" << endl;
					else
						cout << num4 << endl;
				}
				
				for (int i = 0; i <= 9; i++)
				{
					for (int j = 0; j <= 9; j++)
					{
						cout << "* " ;
						if (j == 5)
						{
							break;//break中止嵌套循环中最近的内层循环
						}
					
					}
					cout << endl;
				}

				//案例：九九乘法表
				for (int i1 = 1; i1 <= 9; i1++)
				{
					for (int j1 = 1; j1 <= i1; j1++)
					{
						cout << j1 << "*" << i1 << "=" << i1 * j1 << "\t";
					}
					cout << endl;
				}

				//continue跳转语句
				for (int i2 = 0; i2 <= 10; i2++)
				{
					if (i2 % 2 == 0)
					{
						continue;//continue结束本次循环，继续执行下一次循环
					}
					cout << i2 << endl;
				}




				return 0;
}







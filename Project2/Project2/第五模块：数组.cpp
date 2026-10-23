#include<iostream>
using namespace std;
#include<string>
int main114514()
{

	/*
	1.一维数组：（1）数据类型 数组名【数组长度（元素个数）】 = {元素1，元素2.......}
	注：①可省略数组长度不写，但此时一定要写全后面的元素！！！（系统会自动计算数组长度）/可省略后面{}中元素不写，但一定要写元素个数和下面的元素的赋值！！！
		②数组名第一个元素下标为0！！！最后一个为数组长度-1
		③可用for循环遍历数组，使书写更简洁
		④数组名是一个常量，不能被赋值！！！
				（2）整个数组的内存长度=数组长度（元素个数）*每个元素所占的内存长度（即对应数据类型的字节数，如int为4），可用sizeof（数组名）查看相关信息
				（3）可通过数组名获取数组首地址及每个数组元素地址，直接输出arr及arr[i]即可查看,默认输出十六进制，可用int（arr)强制转化为十进制
		注：①若想查看某个元素的地址，要在arr（数组名）前加上&符号！！！
			②首地址与第一个元素地址相同，后面的均相差相应字节数*字节长度下标！！！
			③若想对数组里的数据进行交换或排序，可使用temp暂时储存数据，写法为int temp=arr[i]   arr[i]=arr[j]   arr[j]=temp的三段式结构
    2.二维数组：（1）最建议的方式：数据类型 数组名【行数】【列数】={ {1,2,3}，{4,5,6}}（为2行3列，仅做举例，书写时尽量换行按照矩阵形式写，更清晰,）
	注：①可省略行数不写，只写列数，计算机可自动算出行数
	    ②两个大括号中间一定要写上逗号！！！
		        （2）二维数组的行数=sizeof(arr)/sizeof(arr[0]  列数=sizeof（arr[0])/sizeof(arr[0][0])
				 (3)首地址查看方式与一维数组基本相同：（int）arr  (int)arr[0]  (int)arr&[0][1]




		*/
	//一维数组定义及最大值取法
	int arr[5] = { 10, 20, 3, 4, 5 };
	int max = 0;
	for (int i = 0; i <= 4; i++)
	{
		cout << arr[i] << endl;
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}
	cout << "数组最大值为：" << max << endl;
	cout << "数组长度为：" << sizeof(arr) << endl;
	cout << "数组首地址为：" << int(arr) << endl;
	cout << "数组第一个元素地址为：" << int(&arr[0]) << endl;
	cout << "数组第二个元素地址为：" << int(&arr[1]) << endl;

	//数组元素逆序：一定用temp储存初始元素！！！
	int arr1[6] = { 1,2,3,4,5,6};
	int start = 0;
	int end = sizeof(arr1) / sizeof(arr1[0]) - 1;//也可直接写成数组元素个数6
	while (start <= end)
	{
	int temp = arr1[start];
	arr1[start] = arr1[end];
	arr1[end] = temp;
		start++, end--;
	}
	cout << "数组逆序之后为：" << endl;
	for (int i = 0; i <= 5; i++)
	{
		cout << arr1[i] << endl;
	}

	//冒泡排序:也应该使用temp
	int arr2[9] = { 2, 5, 4, 6, 7, 9,1,8,3 };
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8 - i; j++)
		{
			if (arr2[j] > arr2[j + 1])
			{
				int temp = arr2[j];
				arr2[j] = arr2[j + 1];
				arr2[j + 1] = temp;
			}
		}
	}
	cout << "冒泡排序结果为：" << endl;
	for (int i = 0; i <= 8; i++)
	{
		cout << arr2[i] << " ";
	}
	cout << endl;
	//二维数组定义
	int arr3[2][3] =
	{ {1,2,3},
	  { 4,5,6 }
	};
	cout << "二维数组的元素为：" << endl;
	for (int i = 0; i <= 1; i++)
	{
		for (int j = 0; j <= 2; j++)
		{
			cout << arr3[i][j] << " ";
		}
		cout << endl;
	}
	cout << "二维数组所占用的内存空间为:" << sizeof(arr3) << endl;
	cout << "二维数组每行所占用的内存空间为:" << sizeof(arr3[0]) << endl;
	cout << "二维数组每个元素所占用的内存空间为:" << sizeof(arr3[0][0]) << endl;
	cout << "二维数组的首地址为：" << (int)arr3 << endl;
	cout << "二维数组第一行元素的首地址为：" << (int)arr3[0] << endl;
	cout << "二维数组第二个元素的首地址为：" << (int)&arr3[0][1] << endl;

	//案例：计算考试总分
	int arr4[3][3] =
	{ {1,2,3},
		{4,5,6},
		{7,8,9}
	};
	string name[3] = { "A","B","C" };
	for(int i=0;i<=2;i++)
		{
		int sum = 0;
		for (int j = 0; j <= 2; j++)
		{
			
			sum += arr4[i][j];
		}
		cout << name[i] << "的总分为：" << sum << endl;


		}
	return 0;
}
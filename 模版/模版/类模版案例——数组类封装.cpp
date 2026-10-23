#include<iostream>
using namespace std;
#include"myarray.hpp"

void printarray1(myarray<int>&arr)
{
	for (int i = 0; i < arr.getsize(); i++)
	{
		cout << arr[i] << " " << endl;
	}
}
void test1()
{
	myarray<int>arr1(10);
	for (int i = 0; i < 10; i++)
	{
		arr1.insert(i);
	}
	printarray1(arr1);
	cout << arr1.getcapacity() << " " << arr1.getsize() << endl;
}


void test()
{
	myarray<int>arr1(5);
	myarray<int>arr2(arr1);
	myarray<int>arr3(100);
	arr3 = arr1;
}
int main()
{
	test();
	test1();
}
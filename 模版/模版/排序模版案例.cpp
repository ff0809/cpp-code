//#include<iostream>
//using namespace std;
//
//template<typename T>
//void swap1(T& a, T& b)
//{
//	T temp = a;
//	a = b;
//	b = temp;
//}
//template<typename T>
//void sort(T arr[], int len)
//{
//	for (int i = 0; i < len - 1; i++)
//	{
//		for (int j = 0; j < len - i - 1; j++)
//		{
//			if (arr[j] > arr[j + 1])
//			{
//				swap1(arr[j], arr[j + 1]);
//			}
//		}
//	}
//}
//template<typename T>
//void printinfo(T arr[], int len)
//{
//	for (int i = 0; i < len; i++)
//	{
//		cout << arr[i] << " ";
//	}
//}
//
//void test1()
//{
//	char arr1[] = "gsjug";
//	int len = sizeof(arr1) / sizeof(char);
//	sort(arr1, len);
//	printinfo(arr1, len);
//}
//void test2()
//{
//	int arr2[] = { 2,6,8,7,4 };
//	int len = sizeof(arr2) / sizeof(arr2[0]);
//	sort(arr2, len);
//	printinfo(arr2, len);
//}
//
//int main()
//{
//	test1();
//	test2();
//}
#include<iostream>
using namespace std;


int myfunction()
{
	double celsius;
	cin >> celsius;
	double fahrenheit = 1.8 * celsius + 32.0;
	cout << "摄氏温度" << celsius << "度对应华氏温度" << fahrenheit << "度。" << endl;

	return 0;
}
int main()
{
	myfunction();
	

	
	return 0;
}
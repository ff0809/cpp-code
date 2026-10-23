#include <conio.h>
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void wait_for_enter()
{
    cout << endl
        << "按回车键继续";
    while (_getch() != '\r')
        ;
    cout << endl
        << endl;
}
void menu()
{
	cout << "***********************************************************" << endl;
    cout << " *      1 矩阵加法       2 矩阵数乘       3 矩阵转置      *" << endl;
	cout << " *      4 矩阵乘法       5 Hadamard乘积   6 卷积运算      *" << endl;
	cout << " *      7 卷积应用       0 退出系统                       *" << endl;
	cout << "***********************************************************" << endl;
	cout << "请输入选择项：" << endl;
}
void matriplus(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& result)
{
	if (A.size() != B.size() || A[0].size() != B[0].size())
	{
		cout << "错误：矩阵A和矩阵B的维数不相等！无法进行加法运算！" << endl;
		return;
	}
	size_t rows = A.size();
	size_t cols = A[0].size();
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			result[i][j] = A[i][j] + B[i][j];
		}
	}
	return;
}
void nummulti(const vector<vector<int>>& A, int num, vector<vector<int>>& result)
{
	size_t rows = A.size();
	size_t cols = A[0].size();
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			result[i][j] = A[i][j] * num;
		}
	}
	return;
}
void matritrans(const vector<vector<int>>& A, vector<vector<int>>& result)
{
	size_t rows = A.size();
	size_t cols = A[0].size();
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			result[j][i] = A[i][j];
		}
	}
	return;
}
void matrimulti(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& result)
{
	if (A[0].size() != B.size())
	{
		cout << "错误：矩阵A的列数不等于B的行数，无法进行乘法运算！" << endl;
		return;
	}
	size_t rows = A.size();
	size_t colsB = B[0].size();
	size_t colsA = A[0].size();
	result.assign(rows, vector<int>(colsB, 0));
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < colsB; ++j)
		{
			for (int k = 0; k < colsA; ++k)
			{
				result[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}

void hadamulti(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& result)
{
	size_t rows = A.size();
	size_t cols = A[0].size();
	result.assign(rows, vector<int>(cols, 0)); 
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			result[i][j] = A[i][j] * B[i][j];
		}
	}
	return;
}

void conv(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& result)
{
	size_t rows = A.size();
	size_t cols = A[0].size();
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			for (int ki = 0; ki < 3; ++ki)
			{
				for (int kj = 0; kj < 3; ++kj)
				{
					// 计算卷积核对应的输入矩阵的位置
					int ni = i + ki - 1;
					int nj = j + kj - 1;

					// 判断是否越界
					if (ni >= 0 && ni < rows && nj >= 0 && nj < cols)
					{
						result[i][j] += A[ni][nj] * B[ki][kj];
					}
				}
			}
		}
	}
}
void demo()
{
	// 1. 加载原图
	Mat image = imread("demolena.jpg", IMREAD_GRAYSCALE); // 加载为灰度图像
	
	// 显示原图
	imshow("原图", image);

	// 2. 定义卷积核
	Mat B1 = (Mat_<float>(3, 3) <<
		1, 1, 1,
		1, 1, 1,
		1, 1, 1);
	Mat B2 = (Mat_<float>(3, 3) <<
		-1, -2, -1,
		0, 0, 0,
		1, 2, 1);
	Mat B3 = (Mat_<float>(3, 3) <<
		-1, 0, 1,
		-2, 0, 2,
		-1, 0, 1);
	Mat B4 = (Mat_<float>(3, 3) <<
		-1, -1, -1,
		-1, 9, -1,
		-1, -1, -1);
	Mat B5 = (Mat_<float>(3, 3) <<
		-1, -1, 0,
		-1, 0, 1,
		0, 1, 1);
	Mat B6 = (Mat_<float>(3, 3) <<
		1, 2, 1,
		2, 4, 2,
		1, 2, 1);

	// 3. 定义卷积核列表和对应的名称列表
	vector<Mat> kernels = { B1, B2, B3, B4, B5, B6 };
	vector<string> kernel_names = { "平滑核", "垂直边缘检测核", "水平边缘检测核", "锐化核", "自定义边缘检测核", "高斯模糊核" };

	// 4. 对每个卷积核进行卷积操作
	for (size_t i = 0; i < kernels.size(); ++i)
	{
		Mat result;
		Mat kernel = kernels[i];

		float kernel_sum = 0.0f;
		for (int r = 0; r < kernel.rows; ++r) {
			for (int c = 0; c < kernel.cols; ++c) {
				kernel_sum += kernel.at<float>(r, c);
			}
		}
		if (kernel_sum != 0)
		{
			kernel /= kernel_sum; // 卷积核归一化
			// 卷积操作
			filter2D(image, result, -1, kernel);
			// 显示卷积结果
			string window_name = "卷积结果 - " + kernel_names[i];
			imshow(window_name, result);
		}
		else {
			cout << "卷积核 " << kernel_names[i] << " 总和为 0，跳过处理" << endl;
		}
	}

	// 5. 等待用户按键后关闭所有窗口
	waitKey(0);
	destroyAllWindows();
}

int main()
{
    // 定义相关变量
	vector<vector<int>> A, B, result;
	int rows, cols,num;

    while (true) // 注意该循环退出的条件
    {
        system("cls"); // 清屏函数

        menu(); 
		char choice;
		choice = _getch();
        if (choice == '0') // 选择退出
        {
			char ch;
            cout << "\n确定退出吗?" << endl;
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
                break;
            else
                continue;
        }

        switch (choice)
        {
        case '1':
			cout << "请输入矩阵A的行数和列数：";
			cin >> rows >> cols;
			A.resize(rows, vector<int>(cols));
			cout << "请输入矩阵A的元素：" << endl;
			for (int i = 0; i < rows; ++i)
			{
				for (int j = 0; j < cols; ++j)
				{
					cin >> A[i][j];
				}
			}
			cout << "请输入矩阵B的行数和列数：";
			cin >> rows >> cols;
			cout << "请输入矩阵B的元素：" << endl;
			B.resize(rows, vector<int>(cols));
			for (int i = 0; i < rows; ++i)
			{
				for (int j = 0; j < cols; ++j)
				{
					cin >> B[i][j];
				}
			}
			matriplus(A, B, result);
			if (A.size() == B.size() && A[0].size() == B[0].size())
			{
				cout << "矩阵加法的结果为 " << endl;
				for (int i = 0; i < rows; ++i)
				{
					for (int j = 0; j < cols; ++j)
					{
						cout << result[i][j] << " ";
					}
					cout << endl;
				}
			}
			wait_for_enter();
			break;
        case '2':
			cout << "请输入矩阵A的行数和列数：";
			cin >> rows >> cols;
			A.resize(rows, vector<int>(cols));
			cout << "请输入矩阵A的元素：" << endl;
			for (int i = 0; i < rows; ++i)
			{
				for (int j = 0; j < cols; ++j)
				{
					cin >> A[i][j];
				}
			}
			cout << "请输入一个数：";
			cin >> num;
			nummulti(A, num, result);
			cout << "矩阵数乘的结果为 " << endl;
			for (int i = 0; i < rows; ++i)
			{
				for (int j = 0; j < cols; ++j)
				{
					cout << result[i][j] << " ";
				}
				cout << endl;
			}
			wait_for_enter();
			break;
        case '3':
			cout << "请输入矩阵A的行数和列数：";
			cin >> rows >> cols;
			A.resize(rows, vector<int>(cols));
			cout << "请输入矩阵A的元素：" << endl;
			for (int i = 0; i < rows; ++i)
			{
				for (int j = 0; j < cols; ++j)
				{
					cin >> A[i][j];
				}
			}
			matritrans(A,result);

			cout << "矩阵转置的结果为 " << endl;
			for (int i = 0; i < cols; ++i)
			{
				for (int j = 0; j < rows; ++j)
				{
					cout << result[i][j] << " ";
				}
				cout << endl;
			}
			wait_for_enter();
			break;
		case '4':
			cout << "请输入矩阵A的行数和列数：";
			cin >> rows >> cols;
			A.resize(rows, vector<int>(cols));
			cout << "请输入矩阵A的元素：" << endl;
			for (int i = 0; i < rows; ++i)
			{
				for (int j = 0; j < cols; ++j)
				{
					cin >> A[i][j];
				}
			}

			cout << "请输入矩阵B的行数和列数：";
			int rowsB, colsB;
			cin >> rowsB >> colsB;
			B.resize(rowsB, vector<int>(colsB));
			cout << "请输入矩阵B的元素：" << endl;
			for (int i = 0; i < rowsB; ++i)
			{
				for (int j = 0; j < colsB; ++j)
				{
					cin >> B[i][j];
				}
			}
			matrimulti(A, B, result);
			if (A[0].size() == B.size())
			{
				cout << "矩阵乘法的结果为：" << endl;
				for (int i = 0; i < result.size(); ++i)
				{
					for (int j = 0; j < result[0].size(); ++j)
					{
						cout << result[i][j] << " ";
					}
					cout << endl;
				}
			}
			wait_for_enter();
			break;

        case '5':
			cout << "请输入矩阵A的行数和列数：";
			cin >> rows >> cols;
			A.resize(rows, vector<int>(cols));
			cout << "请输入矩阵A的元素：" << endl;
			for (int i = 0; i < rows; ++i)
			{
				for (int j = 0; j < cols; ++j)
				{
					cin >> A[i][j];
				}
			}
			cout << "请输入矩阵B的元素：" << endl;
			B.resize(rows, vector<int>(cols));
			for (int i = 0; i < rows; ++i)
			{
				for (int j = 0; j < cols; ++j)
				{
					cin >> B[i][j];
				}
			}
			hadamulti(A,B,result);
			cout << "Hadamard乘积的结果为 " << endl;
			for (int i = 0; i < rows; ++i)
			{
				for (int j = 0; j < cols; ++j)
				{
					cout << result[i][j] << " ";
				}
				cout << endl;
			}
			wait_for_enter();
			break;
        case '6':
			cout << "请输入矩阵A的行数和列数：";
			cin >> rows >> cols;
			A.resize(rows, vector<int>(cols));
			cout << "请输入矩阵A的元素：" << endl;
			for (int i = 0; i < rows; ++i)
			{
				for (int j = 0; j < cols; ++j)
				{
					cin >> A[i][j];
				}
			}
			cout << "请输入卷积核B的元素：" << endl;
			B.resize(3, vector<int>(3));
			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					cin >> B[i][j];
				}
			}
			result.resize(rows, vector<int>(cols));
			conv(A,B,result);
			cout << "卷积运算的结果为 " << endl;
			for (int i = 0; i < rows; ++i)
			{
				for (int j = 0; j < cols; ++j)
				{
					cout << result[i][j] << " ";
				}
				cout << endl;
			}
			wait_for_enter();
			break;
        case '7':
            demo();
			wait_for_enter();
			break;
        default:
            cout << "\n 输入错误，请重新输入" << endl;
            wait_for_enter();
        }
    }
    return 0;
}
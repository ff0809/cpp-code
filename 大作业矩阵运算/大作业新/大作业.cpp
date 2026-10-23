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
	cout << " *      7 卷积应用       8 OTSU算法       9 图像目标提取  *" << endl;
	cout << " *      0 退出系统                                        *" << endl;
	cout << "***********************************************************" << endl;
	cout << "请输入选择项：" << endl;
}
void matriplus(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& result)
{
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
	result.assign(rows, vector<int>(colsB, 0));//确保矩阵乘法后的行数列数分别对应A的行数与B的列数且元素先均初始化为0
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
					int ni = i + ki - 1;//其中减去的1为卷积核的维度除以2得到！！！即为水平方向的零填充长度padding=1
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
	// 加载原图
	Mat image = imread("demolena.jpg", IMREAD_GRAYSCALE); // 加载为灰度图像
	// 显示原图
	imshow("原图", image);

	// 定义卷积核
	Mat B1 = (Mat_<float>(3, 3) <<1, 1, 1,1, 1, 1,1, 1, 1);
	Mat B2 = (Mat_<float>(3, 3) <<-1, -2, -1,0, 0, 0,1, 2, 1);
	Mat B3 = (Mat_<float>(3, 3) <<-1, 0, 1,-2, 0, 2,-1, 0, 1);
	Mat B4 = (Mat_<float>(3, 3) <<-1, -1, -1,-1, 9, -1,-1, -1, -1);
	Mat B5 = (Mat_<float>(3, 3) <<-1, -1, 0,-1, 0, 1,0, 1, 1);
	Mat B6 = (Mat_<float>(3, 3) <<1, 2, 1,2, 4, 2,1, 2, 1);
	vector<Mat> kernels = { B1, B2, B3, B4, B5, B6 };
	vector<string> kernel_names = { "B1平滑核", "B2垂直边缘检测核", "B3水平边缘检测核", "B4锐化核", "B5自定义边缘检测核", "B6高斯模糊核" };//查阅资料得到几个卷积核对应核的实际意义

	for (size_t i = 0; i < kernels.size(); ++i)
	{
		Mat result;
		Mat kernel = kernels[i];

		// 计算卷积核的总和
		float kernel_sum = 0.0;
		for (int r = 0; r < kernel.rows; ++r)
		{
			for (int c = 0; c < kernel.cols; ++c)
			{
				kernel_sum += kernel.at<float>(r, c);
			}
		}
		if (kernel_sum != 0)
		{
			kernel /= kernel_sum;
		}

		// 用Opencv中的filter2D函数进行卷积操作，result存储卷积结果的目标矩阵，-1表示目标图像深度与原图相同
		filter2D(image, result, -1, kernel);

		string window_name = kernel_names[i];
		imshow(window_name, result);
	}
	waitKey(0);
}
void OTSU()
{
	string file = "demolena.jpg";
	Mat image = imread(file, IMREAD_GRAYSCALE); // 加载为灰度图像
	
	Mat binary;
	threshold(image, binary, 0, 255, THRESH_BINARY | THRESH_OTSU); // 大津法（二值法，OTSU）自动寻求全局阈值，无需任何人工干预

	imshow("原图: " + file, image);
	moveWindow("原图: " + file, 100, 100); 

	imshow("OTSU处理: " + file, binary);
	moveWindow("OTSU处理: " + file, 400, 100); // 设置OTSU图像窗口位置，改变x轴位置，防止与原图重叠

	waitKey(0);
}
void extractTargets()
{
	vector<string> image_files = { "snowball.jpg", "polyhedrosis.jpg", "ship.jpg", "brain.jpg" };

	int x_offset = 100; // 初始水平偏移量
	int y_offset = 100; // 初始垂直偏移量
	int step = 200;     // 每个窗口的水平间隔

	for (const string& file : image_files)//依次读取每张待提取图片的循环操作
	{
		Mat image = imread(file, IMREAD_GRAYSCALE); // 加载为灰度图像
		
		// 二值化OTSU阈值处理
		Mat binary;
		threshold(image, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

		// 形态学操作
		Mat morph;
		Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3)); // 定义 3x3 矩形核
		morphologyEx(binary, morph, MORPH_CLOSE, kernel); // 闭运算填充目标区域
		morphologyEx(morph, morph, MORPH_OPEN, kernel);  // 开运算去除噪声

		// 提取目标区域
		Mat result = Mat::zeros(image.size(), image.type()); // 创建黑色背景
		image.copyTo(result, morph); // 使用掩膜保留目标区域

		// 显示原图和处理后的图像
		imshow("原图: " + file, image);
		moveWindow("原图: " + file, x_offset, y_offset);

		imshow("目标提取: " + file, result);
		moveWindow("目标提取: " + file, x_offset + step, y_offset);//形成原图和提取后的图的横向对比，同时避免重叠

		y_offset += 200; // 每次向下移动窗口，避免重叠
	}
	waitKey(0);
}
int main()
{
    // 定义相关变量
	vector<vector<int>> A, B, result;
	int rows, cols, num;

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
			cout << "请输入矩阵A，B的行数和列数：（注意两矩阵行列数均对应相等才能进行加法运算）";
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
			result.resize(rows, vector<int>(cols)); 
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
			result.resize(rows, vector<int>(cols));
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
			result.resize(cols, vector<int>(rows));
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

			cout << "请输入矩阵B的行数和列数：（注意矩阵B的行数和A的列数相等矩阵乘法才有意义）";
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
			result.resize(rows, vector<int>(colsB));
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
			cout << "请输入矩阵A，B的行数和列数：（注意矩阵A，B的行数和列数要相等才能进行该运算）";
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
			result.resize(rows, vector<int>(cols));
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
		case '8':
			OTSU();
			wait_for_enter();
			break;
		case '9':
			extractTargets();
			wait_for_enter();
			break;
        default:
            cout << "\n 输入错误，请重新输入" << endl;
            wait_for_enter();
        }
    }
    return 0;
}
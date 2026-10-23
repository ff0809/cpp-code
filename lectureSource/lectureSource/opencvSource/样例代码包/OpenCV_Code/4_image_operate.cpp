//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//
//int main()
//{
//  /*  string path = "D:\\desktop\\opencv_test\\Project1\\resource\\traffic_signal.png";
//    Mat img = imread(path);*/
//
//    string path = "../resource/noise2.jpg";
//    Mat img = imread(path);
//
//    Mat  result5, imgBlur3, median3;
//    GaussianBlur(img, imgBlur3, Size(3, 3), 0, 0); //高斯模糊
//    blur(img, result5, Size(5, 5)); //均值模糊
//    cv::medianBlur(img, median3, 3);//中值模糊
//
// //   imshow("Image", img);
// //   imshow("result5", result5);
// //   imshow("ImageBlur3", imgBlur3);
//	//imshow("median3", median3);
// 
//    Mat topRow, bottomRow, combined;  // 创建用于存储拼接结果的矩阵
//   
//    hconcat(img, result5, topRow);// 水平拼接第一行   
//    hconcat(imgBlur3, median3, bottomRow); // 水平拼接第二行 
//    vconcat(topRow, bottomRow, combined);// 垂直拼接两行
//    namedWindow("Combined Images", WINDOW_NORMAL);    // 创建可调整大小的窗口
//	resizeWindow("Combined Images", 800, 600); // 设置窗口大小
//    imshow("Combined Images", combined);
//
//    waitKey(0);
//
//    return 0;
//}
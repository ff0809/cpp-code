//#include <opencv2/opencv.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//int main()
//{
//   // string path = "D:\\desktop\\opencv_test\\Project1\\resource\\video.mp4";
//    string path = "../resource/video.mp4";
//    VideoCapture cap(path); // 视频捕捉对象
//
//    // 检查视频文件是否成功打开
//    if (!cap.isOpened()) {
//        cout << "无法打开视频文件！" << endl;
//        return -1;
//    }
//
//    Mat img;
//    while (cap.read(img)) {
//        imshow("Image", img);
//        if (waitKey(1) == 27) { // 按 ESC 键退出循环
//            break;
//        }
//    }
//
//    // 释放视频捕捉对象
//    cap.release();
//    // 关闭所有 OpenCV 窗口
//    destroyAllWindows();
//
//    return 0;
//}
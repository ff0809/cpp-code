//#include <opencv2/opencv.hpp>
//#include <iostream>
//#include <string>
//using namespace cv;
//using namespace std;
//
//// HSV 阈值（全局）
//int hmin = 0, smin = 0, vmin = 0;
//int hmax = 179, smax = 255, vmax = 255;
//
//// 不做任何事，只为了让拖动时更新全局变量
//void on_trackbar(int, void*) {}
//
//// 显示当前 HSV 范围条
//void showColorRange() {
//    Mat bar(50, 300, CV_8UC3);
//    for (int x = 0; x < bar.cols; x++) {
//        Vec3b pix;
//        pix[0] = uchar(hmin + (hmax - hmin) * x / (bar.cols - 1));
//        pix[1] = uchar(smin + (smax - smin) * x / (bar.cols - 1));
//        pix[2] = uchar(vmin + (vmax - vmin) * x / (bar.cols - 1));
//        for (int y = 0; y < bar.rows; y++)
//            bar.at<Vec3b>(y, x) = pix;
//    }
//    cvtColor(bar, bar, COLOR_HSV2BGR);
//    imshow("Color Range", bar);
//}
//
//// 图像处理函数
//void process_and_show(const Mat& img) {
//    Mat hsv, mask, result, gray, edges, drawing;
//    GaussianBlur(img, drawing, Size(5, 5), 1.5);
//    cvtColor(drawing, hsv, COLOR_BGR2HSV);
//    inRange(hsv, Scalar(hmin, smin, vmin), Scalar(hmax, smax, vmax), mask);
//    bitwise_and(img, img, result, mask);
//    cvtColor(result, gray, COLOR_BGR2GRAY);
//    Canny(gray, edges, 50, 150);
//    vector<vector<Point>> contours;
//    findContours(edges, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
//    Mat out = img.clone();
//    for (auto& c : contours) {
//        drawContours(out, vector<vector<Point>>{c}, -1, Scalar(0, 255, 0), 2);
//        Rect r = boundingRect(c);
//        if (r.area() > 1000) rectangle(out, r, Scalar(255, 0, 0), 2);
//    }
//    imshow("Original", img);
//    imshow("Mask", mask);
//    imshow("Result", result);
//    imshow("Edges", edges);
//    imshow("Contours", out);
//}
//
//int main() {
//    cout << "1=文件  2=摄像头: ";
//    int mode; cin >> mode;
//
//    // 创建窗口和Trackbars
//    namedWindow("Trackbars", WINDOW_AUTOSIZE);
//    createTrackbar("Hue Min", "Trackbars", &hmin, 179, on_trackbar);
//    createTrackbar("Hue Max", "Trackbars", &hmax, 179, on_trackbar);
//    createTrackbar("Sat Min", "Trackbars", &smin, 255, on_trackbar);
//    createTrackbar("Sat Max", "Trackbars", &smax, 255, on_trackbar);
//    createTrackbar("Val Min", "Trackbars", &vmin, 255, on_trackbar);
//    createTrackbar("Val Max", "Trackbars", &vmax, 255, on_trackbar);
//
//    Mat img;
//    VideoCapture cap;
//    if (mode == 1) {
//        cout << "图片路径: ";
//        string path; cin >> path;
//        img = imread(path);
//        if (img.empty()) { cerr << "读图失败\n"; return -1; }
//    }
//    else {
//        cap.open(0);
//        if (!cap.isOpened()) { cerr << "打开摄像头失败\n"; return -1; }
//    }
//
//    // 主循环：不断处理并显示，Trackbar 改变全局变量即生效
//    while (true) {
//        if (mode == 2) {
//            cap >> img;
//            if (img.empty()) break;
//        }
//        showColorRange();
//        process_and_show(img);
//
//        char c = (char)waitKey(30);
//        if (c == 27) break;  // ESC 退出
//    }
//
//    return 0;
//}

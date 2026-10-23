// 计算HOG特征
#include "detection_utils.h"

using namespace cv;
using namespace std;

void computeHOGFeatures(const Mat& img, vector<float>& descriptors) {
    HOGDescriptor hog;
    hog.winSize = Size(32, 32);
    hog.blockSize = Size(16, 16);
    hog.blockStride = Size(8, 8);
    hog.cellSize = Size(8, 8);
    hog.nbins = 9;
    hog.compute(img, descriptors);
}

//std::vector<cv::Rect> detect_objects(const std::string& model_save_path, cv::Mat& img, int size = 128, int start_x = 0, int start_y = 0, int end_x = 0, int end_y = 0) {
std::vector<cv::Rect> detect_objects(const std::string& model_save_path, cv::Mat& img, int start_x, int start_y, int end_x, int end_y) {
    // 读取模型
    int size = 128;
    cv::Ptr<cv::ml::SVM> svm = cv::ml::SVM::load(model_save_path);

    // 如果未指定 end_x 和 end_y，则默认为图像的宽度和高度
    if (end_x == 0) end_x = img.cols;
    if (end_y == 0) end_y = img.rows;

    // 存储检测到的边界框
    std::vector<cv::Rect> bboxes;

    // 将图像转换为灰度图像
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

    // 滑动窗口检测
    for (int i = start_y; i < end_y - size; i += 16) { // i是行数，对应的是y坐标
        for (int j = start_x; j < end_x - size; j += 16) { // j是列数，对应的是x坐标
            // 提取窗口区域
            cv::Mat roi = gray(cv::Rect(j, i, size, size));

            // 计算HOG特征
            std::vector<float> descriptors;
            computeHOGFeatures(roi, descriptors);

            // 将特征向量转换为Mat对象
            cv::Mat desc = cv::Mat(descriptors).t();

            // 使用SVM模型进行预测
            float res = svm->predict(desc);

            // 如果预测结果为1，表示检测到目标
            if (res == 1) {
                bboxes.push_back(cv::Rect(j, i, size, size)); // 将边界框添加到列表中
            }
        }
    }
    // 进行非极大值抑制
    bboxes = nonMaximumSuppression(img, bboxes, 0.01);
    return bboxes; // 返回检测到的边界框列表
}
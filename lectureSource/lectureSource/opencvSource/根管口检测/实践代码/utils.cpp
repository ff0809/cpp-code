#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>
#include <opencv2/ml.hpp>
#include <opencv2/objdetect.hpp>
#include <filesystem>

using namespace cv;
using namespace std;


Mat draw_detections(const cv::Mat& img, const std::vector<cv::Rect>& bboxes) {
    cv::Mat result = img.clone();
    for (const auto& bbox : bboxes) {
        cv::rectangle(result, bbox, cv::Scalar(0, 255, 0), 2); // 绘制边界框
    }
    return result;
}

// 计算两个矩形的交并比（IoU）
float computeIoU(const cv::Rect& rect1, const cv::Rect& rect2) {
    cv::Rect inter = rect1 & rect2; // 计算交集
    float interArea = static_cast<float>(inter.area());
    float unionArea = static_cast<float>(rect1.area() + rect2.area() - interArea);
    return interArea / unionArea;
}

// 比较两个矩形的灰度值
float compareGrayscale(const cv::Mat& img, const cv::Rect& rect1, const cv::Rect& rect2) {
    cv::Mat roi1 = img(rect1);
    cv::Mat roi2 = img(rect2);
    double mean1 = cv::mean(roi1)[0]; // 计算第一个矩形的平均灰度值
    double mean2 = cv::mean(roi2)[0]; // 计算第二个矩形的平均灰度值
    return mean1 - mean2; // 返回灰度值的差异
}

// 非极大值抑制（NMS）函数
std::vector<cv::Rect> nonMaximumSuppression(const cv::Mat& img, const std::vector<cv::Rect>& bboxes, float iou_threshold = 0.6) {
    std::vector<cv::Rect> result;
    if (bboxes.empty()) {
        return result; // 如果没有边界框，直接返回空结果
    }

    // img转换为灰度图像
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

    // 按照灰度值从小到大排序（更灰的在前面）
    std::vector<cv::Rect> sorted_bboxes = bboxes;
    std::sort(sorted_bboxes.begin(), sorted_bboxes.end(), [&](const cv::Rect& a, const cv::Rect& b) {
        return compareGrayscale(gray, a, b) > 0;
        });

    while (!sorted_bboxes.empty()) {
        cv::Rect current = sorted_bboxes.back(); // 取出当前最灰的矩形
        sorted_bboxes.pop_back();
        result.push_back(current);

        // 移除与当前矩形IoU大于阈值的矩形
        sorted_bboxes.erase(std::remove_if(sorted_bboxes.begin(), sorted_bboxes.end(), [&](const cv::Rect& rect) {
            return computeIoU(current, rect) > iou_threshold;
            }), sorted_bboxes.end());
    }

    return result;
}

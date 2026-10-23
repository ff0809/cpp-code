#pragma once
#ifndef DETECTION_UTILS_H
#define DETECTION_UTILS_H

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>
#include <opencv2/ml.hpp>
#include <opencv2/objdetect.hpp>
#include <filesystem>

// ÉùÃ÷º¯Êý
cv::Mat draw_detections(const cv::Mat& img, const std::vector<cv::Rect>& bboxes);

float computeIoU(const cv::Rect& rect1, const cv::Rect& rect2);

float compareGrayscale(const cv::Mat& img, const cv::Rect& rect1, const cv::Rect& rect2);

std::vector<cv::Rect> nonMaximumSuppression(const cv::Mat& img, const std::vector<cv::Rect>& bboxes, float iou_threshold = 0.6);

std::vector<cv::Rect> detect_objects(const std::string& model_save_path, cv::Mat& img, int start_x = 0, int start_y = 0, int end_x = 0, int end_y = 0);

void computeHOGFeatures(const cv::Mat& img, std::vector<float>& descriptors);

#endif // DETECTION_UTILS_H
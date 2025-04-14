#include "ShapeDetector.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

bool ShapeDetector::loadImage(const std::string& imagePath) {
    originalImage = cv::imread(imagePath);
    if (originalImage.empty()) {
        std::cerr << "Could not open the image!" << std::endl;
        return false;
    }
    return true;
}

void ShapeDetector::preprocess() {
    cv::cvtColor(originalImage, grayImage, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(grayImage, blurredImage, cv::Size(5, 5), 1.5);
    cv::Canny(blurredImage, edgeImage, 100, 200);
}

void ShapeDetector::detectContours() {
    cv::findContours(edgeImage, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
}

void ShapeDetector::classifyAndLabelShapes() {
    for (size_t i = 0; i < contours.size(); ++i) {
        std::vector<cv::Point> approx;
        double peri = cv::arcLength(contours[i], true);
        cv::approxPolyDP(contours[i], approx, 0.01 * peri, true);

        std::string shapeType;
        if (approx.size() == 3)
            shapeType = "Triangle";
        else if (approx.size() == 4)
            shapeType = "Quadrilateral";
        else if (approx.size() > 15)
            shapeType = "Circle";
        else
            shapeType = "Unknown";

        cv::putText(originalImage, shapeType, approx[0], cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(255, 255, 0), 2);
        cv::drawContours(originalImage, std::vector<std::vector<cv::Point>>{approx}, -1, cv::Scalar(0, 255, 0), 2);
    }
}

void ShapeDetector::displayResult() const {
    cv::imshow("Shape Detection", originalImage);
    cv::waitKey(0);
}

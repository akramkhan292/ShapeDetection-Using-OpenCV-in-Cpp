#ifndef SHAPEDETECTOR_HPP
#define SHAPEDETECTOR_HPP

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

class ShapeDetector {
private:
    cv::Mat originalImage, grayImage, blurredImage, edgeImage;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

public:
    bool loadImage(const std::string& imagePath);
    void preprocess();
    void detectContours();
    void classifyAndLabelShapes();
    void displayResult() const;
};

#endif // SHAPEDETECTOR_HPP
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // Load Image
    Mat image = imread("shapes.jpg");
    if (image.empty()) {
        cout << "Could not open the image!" << endl;
        return -1;
    }
    Mat gray;
    cvtColor(image, gray, COLOR_BGR2GRAY);
    //Apply Gaussian Blur
    Mat blurredImage;
    GaussianBlur(gray, blurredImage, Size(5, 5), 1.5);
    Mat edges;
    Canny(blurredImage, edges, 100, 200);

    // Find contours
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(edges, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
 
    // Draw contours on the original image
    // Mat finalImage = imread("shapes.jpg");
    // drawContours(image, contours, -1, Scalar(0, 255, 0), 2);
   
    for (size_t i = 0; i < contours.size(); i++) {
        vector<Point> approx;
        double peri = arcLength(contours[i], true);
        approxPolyDP(contours[i], approx, 0.01 * peri, true); // Approximate the contour

        if (approx.size() == 3) {
            putText(image, "Triangle", approx[0], FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2);
        } else if (approx.size() == 4) {
            putText(image, "Quadrilateral", approx[0], FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 2);
        } else if (approx.size() > 15) {
            putText(image, "Circle", approx[0], FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2);
        }
        drawContours(image, vector<vector<Point>>{approx}, -1, Scalar(1, 255, 255), 2);
    }
    imshow("Shape Detection", image);

    // Show Original and Blurred Images
    // imshow("Original Image", image);
    // imshow("Gray Image", gray);
    // imshow("Blurred Image", blurredImage);
    // imshow("sketch Image", edges);
    // imshow("Shape Outlined", finalImage);
    
    waitKey(0);
    return 0;
}

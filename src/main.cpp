#include "ShapeDetector.hpp"

int main() {
    ShapeDetector detector;
    if (!detector.loadImage("../data/shapes.jpg")) return -1;

    detector.preprocess();
    detector.detectContours();
    detector.classifyAndLabelShapes();
    detector.displayResult();

    return 0;
}

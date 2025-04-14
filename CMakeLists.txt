cmake_minimum_required(VERSION 3.10)
project(ShapeDetection)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find OpenCV
find_package(OpenCV REQUIRED)

# Include directory for header files (if you have custom headers)
include_directories(${OpenCV_INCLUDE_DIRS} include)

# Add your source file(s)
add_executable(shape_detector src/main.cpp src/ShapeDetector.cpp)

# Link OpenCV libraries
target_link_libraries(shape_detector ${OpenCV_LIBS})

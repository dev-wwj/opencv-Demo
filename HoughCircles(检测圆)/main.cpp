//
//  main.cpp
//  HoughCircles(检察圆)
//
//  Created by wangwenjian on 2022/1/13.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    
    string filename = "circle.webp";
    Mat img = imread(filename, IMREAD_COLOR);
    if (img.empty()) {
        return -1;
    }
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    medianBlur(gray, gray, 5);
    vector<Vec3f> circles;
    HoughCircles(gray, circles, HOUGH_GRADIENT, 1, gray.rows/16, 100, 30, 1, 130);
    
    for (size_t i = 0; i < circles.size(); i++) {
        Vec3i c = circles[i];
        circle(img, Point(c[0], c[1]), c[2], Scalar(0, 0, 255), 3, LINE_AA);
        circle(img, Point(c[0], c[1]), 2, Scalar(0, 255, 0), 3, LINE_AA);
    }
    imshow("origin", gray);
    imshow("detected circles", img);
    moveWindow("origin", gray.cols, 0);
    waitKey();
    return 0;
}

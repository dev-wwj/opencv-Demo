//
//  main.cpp
//  Canny(边缘检测器)
//
//  Created by wangwenjian on 2022/1/13.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

Mat src, src_gray;

Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold;
int const Max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
const char * window_name = "Edge Map";
static void CannyThreshold(int, void *) {
    blur(src_gray, detected_edges, Size(3,3));
    Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * ratio, kernel_size);
    dst = Scalar::all(0);
    src.copyTo(dst, detected_edges);
    imshow(window_name, dst);
}

int main(int argc, const char * argv[]) {
    src = imread("146_.jpg", IMREAD_COLOR);
    if (src.empty()) {
        return -1;
    }
    dst.create(src.size(), src.type());
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    namedWindow(window_name, WINDOW_AUTOSIZE);
    createTrackbar("Min Threshold", window_name, &lowThreshold, Max_lowThreshold, CannyThreshold);
    CannyThreshold(0,0);
    waitKey(0);
    return 0;
}

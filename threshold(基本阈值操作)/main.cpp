//
//  main.cpp
//  threshold(基本阈值操作)
//
//  Created by wangwenjian on 2022/1/10.
//

#include <iostream>

#include <opencv2/opencv.hpp>

using namespace cv;

int threshold_value = 0;
int threshold_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

Mat src, src_gray, dst;

const char* window_name = "Threshold Demo";
const char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
const char* trackbar_value = "Value";

void Threshold_Demo( int, void* );


int main(int argc, const char * argv[]) {
    // insert code here...
    String imageName("148_.jpg");
    if (argc > 1) {
        imageName = argv[1];
    }
    src = imread(imageName, IMREAD_COLOR);
    if (src.empty()) {
        return -1;
    }
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    namedWindow(window_name, WINDOW_AUTOSIZE);
    createTrackbar(trackbar_type, window_name, &threshold_type, max_type, Threshold_Demo);
    createTrackbar(trackbar_value, window_name, &threshold_value, max_value, Threshold_Demo);
    Threshold_Demo(0, 0);
    for (;;) {
        char c = (char)waitKey( 20);
        if (c == 27) {
            break;
        }
    }
    return 0;
}

void Threshold_Demo( int, void* ) {
    threshold(src_gray, dst, threshold_value, max_BINARY_value, threshold_type);
    imshow(window_name, dst);
}

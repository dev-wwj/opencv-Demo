//
//  main.cpp
//  filter2D(线性滤镜)
//
//  Created by wangwenjian on 2022/1/13.
//

#include <iostream>

#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, const char ** argv) {
    Mat src, dst;
    Mat kernel;
    Point anchor;
    double delta;
    int ddepth;
    int kernel_size;
    
    const char* window_name = "filter2D Demo";
    String imageName("146_.jpg");
    if (argc > 1) {
        imageName = argv[1];
    }
    src = imread(imageName, IMREAD_COLOR);
    if (src.empty()) {
        return -1;
    }
    anchor = Point(-1, -1);
    delta = 0;
    ddepth = -1;
    int ind = 0;
    for (; ; ) {
        char c = (char)waitKey(500);
        if (c == 27) {
            break;
        }
        kernel_size = 3 + 2 * (ind % 5);
        kernel = Mat::ones(kernel_size, kernel_size, CV_32F)/(float)(kernel_size * kernel_size);
        filter2D(src, dst, ddepth, kernel,anchor,delta, BORDER_DEFAULT);
        imshow(window_name, dst);
        ind ++ ;
    }
    return 0;
    
}

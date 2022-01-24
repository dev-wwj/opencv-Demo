//
//  main.cpp
//  equalizeHist(直方图同等化)
//
//  Created by wangwenjian on 2022/1/14.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    Mat src, dst;
    const char* source_window = "Source image";
    const char* equalized_window = "Equalized Image";
    src = imread("148_.jpg",IMREAD_COLOR);
    if (src.empty()) {
        return -1;
    }
    cvtColor(src, src, COLOR_BGR2GRAY);
    equalizeHist(src, dst);
    namedWindow(source_window, WINDOW_AUTOSIZE);
    namedWindow(equalized_window, WINDOW_AUTOSIZE);
    imshow(source_window, src);
    imshow(equalized_window, dst);
    waitKey(0);
    return 0;
}

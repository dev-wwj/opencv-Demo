//
//  main.cpp
//  Laplacian(拉普拉斯&梯度运算)
//
//  Created by wangwenjian on 2022/1/13.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, const char * argv[]) {
    // insert code here...
    Mat src, src_gray, dst;
    int kernel_size = 3;
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;
    const char *window_name = "Laplace Demo";
    String imageName("148_.jpg");
    if (argc > 1) {
        imageName = argv[1];
    }
    src = imread(imageName, IMREAD_COLOR);
    if (src.empty()) {
        return -1;
    }
    GaussianBlur(src, src, Size(3,3), 0, 0, BORDER_DEFAULT);
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    Mat abs_dst;
    Laplacian(src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(dst, abs_dst);
    imshow(window_name, abs_dst);
    waitKey(0);
    return 0;
}

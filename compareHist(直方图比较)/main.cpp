//
//  main.cpp
//  compareHist(直方图比较)
//
//  Created by wangwenjian on 2022/1/14.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    Mat src_base, hsv_base;
    Mat src_test1, hsv_test1;
    Mat src_test2, hsv_test2;
    Mat hsv_half_down;
    
    src_base = imread("146_.jpg", IMREAD_COLOR);
    src_test1 = imread("147_.jpg", IMREAD_COLOR);
    src_test2 = imread("148_.jpg", IMREAD_COLOR);
    if (src_base.empty() || src_test1.empty() || src_test2.empty()) {
        return -1;
    }
    cvtColor(src_base, hsv_base, COLOR_BGR2HSV);
    cvtColor(src_test1, hsv_test1, COLOR_BGR2HSV);
    cvtColor(src_test2, hsv_test2, COLOR_BGR2HSV);
    hsv_half_down = hsv_base( Range(hsv_base.rows/2, hsv_base.rows - 1), Range(0, hsv_base.cols - 1));
    int h_bins = 50;
    int s_bins = 60;
    int histSize[] = {h_bins, s_bins};
    float h_ranges[] = {0, 180};
    float s_ranges[] = {0, 256};
    const float* ranges[] = {h_ranges, s_ranges};
    int channels[] = {0, 1};
    MatND hist_base;
    MatND hist_half_down;
    MatND hist_test1;
    MatND hist_test2;
    calcHist(&hsv_base, 1, channels, Mat(), hist_base, 2, histSize, ranges, true, false);
    normalize(hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat());
    calcHist(&hsv_half_down, 1, channels, Mat(), hist_half_down, 2, histSize, ranges, true, false);
    normalize(hist_half_down, hist_half_down, 0, 1, NORM_MINMAX, -1, Mat());
    calcHist(&hsv_test1, 1, channels, Mat(), hist_test1, 2, histSize, ranges, true, false);
    normalize(hist_test1, hist_test1, 0, 1, NORM_MINMAX, -1, Mat());
    calcHist(&hsv_test2, 1, channels, Mat(), hist_test2, 2, histSize, ranges, true, false);
    normalize(hist_test2, hist_test2, 0, 1, NORM_MINMAX, -1, Mat());
    
    for (int i = 0; i < 4; i++) {
        int compare_mathod = i;
        double base_base = compareHist(hist_base, hist_base, compare_mathod);
        double base_half = compareHist(hist_base, hist_half_down, compare_mathod);
        double base_test1 = compareHist(hist_base, hist_test1, compare_mathod);
        double base_test2 = compareHist(hist_base, hist_test2, compare_mathod);
        printf("Method [%d] Perfect, Base-Half, Base-Test(1), Base-Test(2),: %f, %f, %f, %f \n", i, base_base, base_half, base_test1, base_test2);
        
    }
    printf("Done \n");
    return 0;
}

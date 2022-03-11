//
//  main.cpp
//  提取前景
//
//  Created by wangwenjian on 2022/2/10.
//

#include <iostream>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
RNG rng(12345);

int main(int argc, const char * argv[]) {
    // insert code here...
    
    Mat src = imread("109_.jpg");
    if (!src.data) {
        return -1;
    }
    imshow("Source Image", src);
    for (int x = 0 ; x < src.rows; x++) {
        for (int y = 0 ; y < src.cols; y++) {
            if (src.at<Vec3b>(x, y) == Vec3b(255,255,255)) {
                src.at<Vec3b>(x, y)[0] = 0;
                src.at<Vec3b>(x, y)[1] = 0;
                src.at<Vec3b>(x, y)[2] = 0;
            }
        }
    }
    imshow("Black Background Image", src);
    
    Mat kernel = (Mat_<float>(3,3) <<
                  1, 1, 1,
                  1, -8, 1,
                  1, 1, 1);
    
    Mat imgLaplacian;
    Mat sharp = src;
    filter2D(sharp, imgLaplacian, CV_32F, kernel);
    src.convertTo(sharp, CV_32F);
    Mat imgResult = sharp - imgLaplacian;
    imgResult.convertTo(imgResult, CV_8UC3);
    imgLaplacian.convertTo(imgLaplacian, CV_8UC3);
    imshow("New Sharped Image", imgResult);
    src = imgResult;
    Mat bw;
    cvtColor(src, bw, COLOR_BGR2GRAY);
    
    threshold(bw, bw, 127, 255, THRESH_BINARY | THRESH_OTSU);
    imshow("Binary Image", bw);

    Mat threshold_output;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    threshold(bw, threshold_output, 127, 255, THRESH_BINARY_INV);
    findContours(bw, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
    vector<vector<Point>> contours_poly(contours.size());
    Rect rect ;
    for (size_t i = 0; i < contours.size(); i++) {
        approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
        Rect temp = boundingRect(Mat(contours_poly[i]));
        if (temp == Rect(0,0,bw.cols,bw.rows)) {
            continue;
        }
        rect = rect | boundingRect(Mat(contours_poly[i]));
    }
    Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
    Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));

    rectangle(drawing, rect.tl(), rect.br(), color, 2, 8, 0);

    namedWindow("Contours", WINDOW_AUTOSIZE);
    imshow("Contours", drawing);

    
    waitKey();
    return 0;
}

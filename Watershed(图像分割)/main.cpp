//
//  main.cpp
//  Watershed(图像分割)
//
//  Created by wangwenjian on 2022/1/21.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    
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
    
    threshold(bw, bw, 40, 255, THRESH_BINARY | THRESH_OTSU);
    imshow("Binary Image", bw);
    
    Mat dist;
    distanceTransform(bw, dist, DIST_L2, 3);
    
    normalize(dist, dist, 0, 1., NORM_MINMAX);
    imshow("Distance Transform Image", dist);
    
    threshold(dist, dist, .4, 1., THRESH_BINARY);
    
    Mat kernel1 = Mat::ones(3, 3, CV_8UC1);
    dilate(dist, dist, kernel1);
    imshow("Peaks", dist);
    
    Mat dist_8u;
    dist.convertTo(dist_8u, CV_8U);
    
    vector<vector<Point>> contours;
    findContours(dist_8u, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    
    Mat markers = Mat::zeros(dist.size(), CV_32SC1);
      // Draw the foreground markers
    for (size_t i = 0; i < contours.size(); i++)
        drawContours(markers, contours, static_cast<int>(i), Scalar::all(static_cast<int>(i)+1), -1);
      // Draw the background marker
    circle(markers, Point(5,5), 3, CV_RGB(255,255,255), -1);
//    imshow("Markers", markers);
    
    watershed(src, markers);
    Mat mark = Mat::zeros(markers.size(), CV_8UC1);
    markers.convertTo(mark, CV_8UC1);
    bitwise_not(mark, mark);
    
    vector<Vec3b> colors;
    for (size_t i = 0 ; i < contours.size(); i++) {
        int b = theRNG().uniform(0, 255);
        int g = theRNG().uniform(0, 255);
        int r = theRNG().uniform(0, 255);
        colors.push_back(Vec3b((uchar)b,(uchar)g,(uchar)r));
    }
    
    Mat dst = Mat::zeros(markers.size(), CV_8UC3);
    for (int i = 0; i < markers.rows; i++) {
        for (int j = 0; j < markers.cols; j++) {
            int index = markers.at<int>(i, j);
            if (index > 0 && index <= static_cast<int>(contours.size())) {
                dst.at<Vec3b>(i, j) = colors[index - 1];
            }else {
                dst.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
            }
        }
    }
    imshow("Final Result", dst);
    waitKey(0);
    
    return 0;
}

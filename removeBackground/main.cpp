//
//  main.cpp
//  removeBackground
//
//  Created by wangwenjian on 2022/2/15.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;



void shap(Mat mask);
void bianyuanchuli();

Mat src;

int main(int argc, const char * argv[]) {
    // insert code here...
    src = imread("8e9e.png", IMREAD_COLOR);
    resize(src, src, Size(src.cols/2, src.rows /2));
    
    namedWindow("origin", WINDOW_AUTOSIZE);
    imshow("origin", src);
    
    Mat hsv;
    cvtColor(src, hsv, COLOR_BGR2HSV);
    
    
    int low_r = 70, low_g = 70, low_b = 70;
    int high_r = 255, high_g = 255, high_b = 255;
    Mat mask;
    inRange(hsv, Scalar(low_b, low_g, low_r), Scalar(high_b, high_g, high_r), mask);
    namedWindow("mask", WINDOW_AUTOSIZE);
    imshow("mask", mask);
        
    shap(mask);
    
   

//    for (int i = 0; i < pm.rows; i++) {
//        for (int j = 0; j < pm.cols; j++) {
//
//        }
//    }


    waitKey(0);
    return 0;
}

void shap(Mat mask) {
    // 腐蚀
    Mat kernel = Mat::ones(4, 4, CV_8UC1);
    Mat erode;
    cv::erode(mask, erode, kernel);
    namedWindow("kernel", WINDOW_AUTOSIZE);
    imshow("kernel", erode);
    
    // 膨胀
    Mat kernel1 = Mat::ones(2, 2, CV_8UC1);
    Mat dilate;
    cv::dilate(erode, dilate, kernel1, Point(-1, -1), 3);
    namedWindow("dilate", WINDOW_AUTOSIZE);
    imshow("dilate", dilate);
    
    for (int i = 0 ; i < mask.rows; i++) {
        for (int j = 0 ; j < mask.cols; j++) {
            Vec3b bb = dilate.at<Vec3b>(i, j);
            if (dilate.at<Vec3b>(i, j)[0] == 255) {
                mask.at<Vec3b>(i, j) = Vec3b(0, 0, 255);
            }
        }
    }
    namedWindow("src", WINDOW_AUTOSIZE);
    imshow("src", src);
    bianyuanchuli();
}

void bianyuanchuli() {
    Mat canny_output;
    Mat img_copy = Mat::zeros(src.size(), CV_8UC3);
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    Canny(src, canny_output, 100, 255, 3);
    namedWindow("imgCanny", WINDOW_AUTOSIZE);
    imshow("imgCanny", canny_output);
    
    Mat pm;
    resize(canny_output, pm, Size(src.cols/10, src.rows /10));
    cout << "pm =" << endl << "" << pm << endl << endl;
    
    Mat g1 =  getStructuringElement(MORPH_RECT, Size(5,5));
    Mat g2 =  getStructuringElement(MORPH_RECT, Size(7,7));

    Mat dilate;
    cv::dilate(canny_output, dilate, g1, Point(-1, -1), 1);
    namedWindow("img_dilate", WINDOW_AUTOSIZE);
    imshow("img_dilate", dilate);
    Mat dilate2;
    cv::dilate(canny_output, dilate2, g2, Point(-1, -1), 1);
    namedWindow("img_dilate2", WINDOW_AUTOSIZE);
    imshow("img_dilate2", dilate2);

    for (int i = 0; i< dilate.rows; i++) {
        for (int j = 0; i < dilate.cols; i++) {
            if (dilate2.at<Vec3b>(i, j)[0] == 0) {
                src.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
            }
        }
    }
    namedWindow("dst1", WINDOW_AUTOSIZE);
    imshow("dst1", src);

    Mat dst;
    GaussianBlur(src, dst, Size(3,3), 0);

    for (int i = 0; i< dilate.rows; i++) {
        for (int j = 0; i < dilate.cols; i++) {
            if (dilate.at<Vec3b>(i, j)[0] != 0) {
                img_copy.at<Vec3b>(i, j) = dst.at<Vec3b>(i, j);
            }
        }
    }

    namedWindow("dst", WINDOW_AUTOSIZE);
    imshow("dst", img_copy);
}

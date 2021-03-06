//
//  main.cpp
//  inRange(阈值操作)
//
//  Created by wangwenjian on 2022/1/11.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdlib.h>

using namespace std;
using namespace cv;

void on_low_r_thresh_trackbar(int, void *);
void on_high_r_thresh_trackbar(int, void *);
void on_low_g_thresh_trackbar(int, void *);
void on_high_g_thresh_trackbar(int, void *);
void on_low_b_thresh_trackbar(int, void *);
void on_high_b_thresh_trackbar(int, void *);

int low_r = 30, low_g = 30, low_b = 30;
int high_r = 100, high_g = 100, high_b = 100;

int main(int argc, const char * argv[]) {
    // insert code here...
    Mat frame, frame_threshold;
    const string source = "201.mp4";
    
    
    VideoCapture cap(source);
    namedWindow("Video Capture", WINDOW_NORMAL);
    namedWindow("Object Detection", WINDOW_NORMAL);
    
    createTrackbar("Low R", "Object Detection", &low_r, 255, on_low_r_thresh_trackbar);
    createTrackbar("High R", "Object Detection", &high_r, 255, on_high_r_thresh_trackbar);
    createTrackbar("Low G", "Object Detection", &low_g, 255, on_low_g_thresh_trackbar);
    createTrackbar("High G", "Object Detection", &high_g, 255, on_high_g_thresh_trackbar);
    createTrackbar("Low B", "Object Detection", &low_b, 255, on_low_b_thresh_trackbar);
    createTrackbar("High B", "Object Detection", &high_b, 255, on_high_b_thresh_trackbar);
    
    while ((char)waitKey(1) != 'q') {
        cap >> frame;
        if (frame.empty()) {
            break;
        }
        inRange(frame, Scalar(low_b, low_g, low_r), Scalar(high_b, high_g, high_r), frame_threshold);
        imshow("Video Capture", frame);
        imshow("Object Detection", frame_threshold);
    }
    return 0;
}

void on_low_r_thresh_trackbar(int, void *) {
    low_r = min(high_r - 1 , low_r);
    setTrackbarPos("Low R", "Object Detection", low_r);
}

void on_high_r_thresh_trackbar(int, void *) {
    high_r = max(high_r , low_r + 1);
    setTrackbarPos("High R", "Object Detection", high_r);
}

void on_low_g_thresh_trackbar(int, void *) {
    low_g = min(high_g -1, low_g);
    setTrackbarPos("Low G", "Object Detection", low_g);
}

void on_high_g_thresh_trackbar(int, void *) {
    high_g = max(high_g, low_g + 1);
    setTrackbarPos("High G", "Object Detection", high_g);
}

void on_low_b_thresh_trackbar(int, void *) {
    low_b = min(high_b - 1, low_b);
    setTrackbarPos("Low B", "Object Detection", low_b);
}

void on_high_b_thresh_trackbar(int, void *) {
    high_b = max(high_b, low_b + 1);
    setTrackbarPos("High B", "Object Detection", high_b);
}

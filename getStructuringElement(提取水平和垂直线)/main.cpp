//
//  main.cpp
//  getStructuringElement(提取水平和垂直线)
//
//  Created by wangwenjian on 2022/1/10.
//

#include <iostream>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    // insert code here...
    Mat src = imread("150_.png");
    if (!src.data) {
        cerr << "Problem loading image!!!" << endl;
    }
    imshow("src", src);
    
    Mat gray;
    if (src.channels() == 3) {
        cvtColor(src, gray, COLOR_BGR2GRAY);
    } else {
        gray = src;
    }
    
    imshow("gray", gray);
    moveWindow("gray", 0, src.rows / 2 );
    
    Mat bw;
    adaptiveThreshold(~gray, bw, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);
    imshow("binary", bw);
    moveWindow("binary", 0, src.rows / 2  * 2);

    Mat horizontal = bw.clone();
    Mat vertical = bw.clone();
    
    int horizontalsize = horizontal.cols/ 30;
    Mat horizontalStructure = getStructuringElement(MORPH_RECT, Size(horizontalsize,1));
    erode(horizontal, horizontal, horizontalStructure, Point(-1, -1));
    dilate(horizontal, horizontal, horizontalStructure, Point(-1, -1));
    imshow("horizontal", horizontal);
    moveWindow("horizontal", 0, src.rows / 2  * 3);

    int verticalsize = vertical.rows / 30;
    Mat verticalStructure = getStructuringElement(MORPH_RECT, Size(1, verticalsize));
    
    erode(vertical, vertical, verticalStructure, Point(-1, -1));
    dilate(vertical, vertical, verticalStructure, Point(-1, -1));
    imshow("vertical", vertical);
    moveWindow("vertical", 0, src.rows / 2  * 4);

    bitwise_not(vertical, vertical);
    
    imshow("vertical_bit", vertical);
    moveWindow("vertical_bit", 0, src.rows / 2  * 5);

    // Extract edges and smooth image according to the logic
       // 1. extract edges
       // 2. dilate(edges)
       // 3. src.copyTo(smooth)
       // 4. blur smooth img
       // 5. smooth.copyTo(src, edges)
    // Step 1
    Mat edges;
    adaptiveThreshold(vertical, edges, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, -2);
    imshow("edges", edges);
    moveWindow("edges", 0, src.rows / 2  * 6);

    // Step2
    Mat kernel = Mat::ones(2, 2, CV_8UC1);
    dilate(edges, edges, kernel);
    imshow("dilate", edges);
    moveWindow("dilate", 0, src.rows / 2  * 7);

    // Step3
    Mat smooth;
    vertical.copyTo(smooth);
    
    // Step4
    blur(smooth, smooth, Size(2,2));
    
    // Step5
    smooth.copyTo(vertical, edges);
    
    // Show final result
    imshow("smooth", vertical);
    moveWindow("smooth", 0, src.rows / 2  * 8);

    waitKey(0);
    
    return 0;
}

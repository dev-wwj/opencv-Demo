//
//  main.cpp
//  HOGDescriptor(人物检测)
//
//  Created by wangwenjian on 2022/2/16.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    
    Mat src = imread("151_.png", COLOR_BGR2GRAY);
    Mat dst = src.clone();
    //SVM分类器
    HOGDescriptor hog = HOGDescriptor();
    hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
    vector<Rect> findrects, findrect;
    //多尺度检测
    hog.detectMultiScale(src, findrects);
    //若rects有嵌套,则取最外面的矩形存入rect
    for(int i=0; i < findrects.size(); i++)
    {
        Rect rect = findrects[i];
        int j=0;
        for(; j < findrects.size(); j++)
            if(j != i && (rect & findrects[j]) == rect)
                break;
        if( j == findrects.size())
            findrect.push_back(rect);
    }
  
    //框选出检测结果
    for(int i=0; i<findrects.size(); i++)
    {
        Rect rect = findrects[i];
        RNG rng(i);
        Scalar color = Scalar(rng.uniform(0,255), rng.uniform(0,255), rng.uniform(0,255));
        rectangle(dst, rect.tl(), rect.br(), color, 2);
    }
    namedWindow("src", WINDOW_AUTOSIZE);
    imshow("src", src);
    namedWindow("dst", WINDOW_AUTOSIZE);
    imshow("dst", dst);
    waitKey();
    return 0;
}

//
//  main.cpp
//  grabCut(前景提取)
//
//  Created by wangwenjian on 2022/2/10.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int numRun = 0;
Rect rect;
bool init = false;
Mat src, image;

Mat mask, bgModel, fgModel;

const char * winTitle = "input image";

void onMouse(int event, int x, int y, int flags, void * param);
void setROIMask();
void showImage();
void runGrabCut();

int main(int argc, const char * argv[]) {
    // insert code here...
    Mat s = imread("8e9e.png", IMREAD_COLOR);
    Size size = Size(s.cols/2, s.rows/2);
    pyrDown(s, src, size);
    GaussianBlur(src, src, Size(5,5), 0, 0, BORDER_DEFAULT);

    if (src.empty()) {
        return -1;
    }
    mask.create(src.size(), CV_8UC1);
    mask.setTo(Scalar::all(GC_BGD));   // mask 设置为背景
    
    namedWindow(winTitle, WINDOW_AUTOSIZE);
    
    setMouseCallback(winTitle, onMouse);
    imshow(winTitle, src);   // 原图
    
    while (true) {
        char c = (char)waitKey(0);
        
        if (c == 'n') {
            runGrabCut();  //开始割图算法
            numRun ++;  // 迭代次数加1
            showImage();   // 显示图像
            //imshow("背景",bgModel);
            //imshow("前景",fgModel);
            cout << "迭代次数为：" << numRun << endl;
        }
        if ((int)c ==  27) {
            break; //检测到按下esc按钮
        }
    }
    waitKey(0);
    return 0;
}

void showImage() {
    Mat result, binMask;
    binMask.create(mask.size(), CV_8UC1);
    binMask = mask & 1;
    if (init) {
        src.copyTo(result, binMask);
    } else {
        src.copyTo(result);
    }
    rectangle(result, rect, Scalar(0,0, 255), 2, 8);  // 矩形
    imshow(winTitle, result);
}



void setROIMask() {
    //GC_BGD=0----背景
    //GC_FGD=1----前景
    //GC_PR_BGD=2----可能为背景
    //GC_PR_FGD=3----可能为前景

    mask.setTo(GC_BGD);   // 全部设置为背景
    rect.x = max(0, rect.x);
    rect.y = max(0, rect.y);
    
    rect.width = min(rect.width, src.cols - rect.x);
    rect.height = min(rect.height, src.rows - rect.y);
    
    mask(rect).setTo(Scalar(GC_PR_FGD));  //将矩形区域设置为可能的前景
}

void onMouse(int event, int x, int y, int flags, void * param) {
    switch (event) {
        case EVENT_LBUTTONDOWN:
            rect.x = x;
            rect.y = y;
            rect.width = 1;
            rect.height = 1;
            init = false;
            numRun = 0;
            break;
            
        case EVENT_MOUSEMOVE:
            if (flags & EVENT_FLAG_LBUTTON) {
                rect = Rect(Point(rect.x, rect.y), Point(x, y));
                showImage();
            }
            break;
            
        case EVENT_LBUTTONUP:
            if (rect.width > 1 && rect.height > 1) {
                setROIMask();
                showImage();
            }
            break;
        default:
            break;
    }
}

void runGrabCut() {
    if (rect.width < 2 || rect.height < 2) {
        return;
    }
    if (init) {
        grabCut(src, mask, rect, bgModel, fgModel, 1);
    }else {
        grabCut(src, mask, rect, bgModel, fgModel, 1, GC_INIT_WITH_RECT);
        init = true;
    }
}

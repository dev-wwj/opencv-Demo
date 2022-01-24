//
//  main.cpp
//  copyMakeBorder(添加边框)
//
//  Created by wangwenjian on 2022/1/13.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
Mat src, dst;
int top, bottom, left, right;;
int borderType;

const char* window_name = "copyMakeBorder Demo";
RNG rng(12345);

int main(int argc, const char * argv[]) {
    String imageName("146_.jpg");
    if (argc > 1) {
        imageName = argv[1];
    }
    src = imread(imageName, IMREAD_COLOR);
    if (src.empty()) {
        return -1;
    }
    printf( "\n \t copyMakeBorder Demo: \n");
    printf( "\t -------------- \n");
    printf( " ** Press 'c' to set the border to a random constant value \n");
    printf( " ** Press 'r' to set the border to be replicated \n");
    printf( " ** Press 's' to set the border to be reflect \n");
    printf( " ** Press 'w' to set the border to be wrap \n");
//    printf( " ** Press 't' to set the border to be transparent \n");
    printf( " ** Press 'd' to set the border to be default \n");
    printf( " ** Press 'i' to set the border to be isolated \n");
    printf( " ** press 'ESC' to exit the program \n");
    namedWindow(window_name, WINDOW_AUTOSIZE);
    top = (int) (0.05 *src.rows);
    bottom = (int) (0.05 * src.rows);
    left = (int) (0.05 *src.cols);
    right = (int) (0.05 *src.cols);
    dst = src;
    imshow(window_name, dst);
    
    for (;;) {
        char c = (char)waitKey(500);
        if (c == 27) {
            break;
        }else if(c == 'c') {
            borderType = BORDER_CONSTANT;
        }else if(c == 'r') {
            borderType = BORDER_REPLICATE;
        }else if(c == 's') {
            borderType = BORDER_REFLECT;
        }else if(c == 'w') {
            borderType = BORDER_WRAP;
        }
//        else if(c == 't') {
//            borderType = BORDER_TRANSPARENT;
//        }
        else if(c == 'd') {
            borderType = BORDER_DEFAULT;
        }else if(c == 'i') {
            borderType = BORDER_ISOLATED;
        }
        Scalar value(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        copyMakeBorder(src, dst, top, bottom
                       , left, right, borderType, value);
        imshow(window_name, dst);
    }
    return 0;
}

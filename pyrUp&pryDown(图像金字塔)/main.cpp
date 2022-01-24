//
//  main.cpp
//  pyrUp&pryDown(图像金字塔)
//
//  Created by wangwenjian on 2022/1/10.
//

#include <iostream>

#include <opencv2/opencv.hpp>

using namespace cv;
Mat src, dst, tmp;
const char *window_name = "Pyramids Demo";

int main(int argc, const char * argv[]) {
    // insert code here...
    printf( "\n Zoom In-Out demo  \n " );
    printf( "------------------ \n" );
    printf( " * [u] -> Zoom in  \n" );
    printf( " * [d] -> Zoom out \n" );
    printf( " * [ESC] -> Close program \n \n" );
    src = imread("148_.jpg");
    if (src.empty()) {
        printf(" No data! -- Exiting the program \n" );
        return -1;
    }
    tmp = src;
    dst = tmp;
    imshow(window_name, dst);
    for (;;) {
        char c = (char)waitKey(0);
        if (c == 27) {
            break;
        }
        if (c == 'u') {
            pyrUp(tmp, dst, Size(tmp.cols * 2, tmp.rows *2));
            printf( "** Zoom In: Image * 2 \n");
        } else if (c == 'd') {
            pyrDown(tmp, dst, Size(tmp.cols/2, tmp.rows/2));
            printf( "** Zoom In: Image / 2 \n");
        }
        imshow(window_name, dst);
        tmp = dst;
    }
    return 0;
}

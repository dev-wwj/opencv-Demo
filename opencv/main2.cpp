//
//  main2.cpp
//  opencv
//
//  Created by wangwenjian on 2022/1/5.
//

#include "main2.hpp"

#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;

static void help(char * progName) {
    cout << endl << "This program demonstrated the use of the discrete Fourier transform (DFT)." << endl << "The dft of an image is taken and it's power spectrum is displayed." << endl << "Usage:" << endl << progName << "[image_name -- default ../data/lena.jpg]" << endl << endl;
}

int main(int argc, char ** argv) {
    help(argv[0]);
    const char* fileName = "148_.jpg";
    
    Mat I = imread(fileName, IMREAD_COLOR);
    if (I.empty()) {
        return -1;
    }
    Mat padded;
    int m = getOptimalDFTSize(I.rows);
    int n = getOptimalDFTSize(I.cols);
    copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));
    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);
    
    dft(complexI, complexI);
    
    split(complexI, planes);
    
    magnitude(planes[0], planes[1], planes[0]);
    Mat magI = planes[0];
    
    magI += Scalar::all(1);
    
    log(magI, magI);
    
    magI = magI(Rect(0, 0, magI.cols & -2 , magI.rows & -2));
    
    int cx = magI.cols/2;
    int cy = magI.rows/2;
    
    Mat q0(magI, Rect(0, 0, cx, cy));
    Mat q1(magI, Rect(cx, 0, cx, cy));
    Mat q2(magI, Rect(0, cy, cx, cy));
    Mat q3(magI, Rect(cx, cy, cx, cy));
    
    Mat tmp;
    
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);
    
    normalize(magI, magI, 0, 1, NORM_MINMAX);
    
    imshow("Input Image", I);
    imshow("spectrum magnitude", magI);
    
    waitKey();
    
    return 0;

}

//
//  main.cpp
//  opencv
//
//  Created by wangwenjian on 2022/1/4.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//int main(int argc, const char * argv[]) {
    // Code1
//    std::cout << "Hello, World!\n";
//    Mat image  = imread("IMG_7774.JPG",IMREAD_REDUCED_GRAYSCALE_2);
//    if (!image.data) {
//        cout << "无法读取图片" << endl ;
//        return -1;
//    }
//    namedWindow("Display window", WINDOW_AUTOSIZE);
//    imshow("img", image);
//    waitKey(0);
//    return 0;
    
    // Code2  Mat构造函数
//    Mat M(3,3, CV_8UC3, Scalar(0, 0, 255));
//    cout << "M =" << endl << "" << M << endl << endl;
    
    // Code3  函数填入随机值的矩阵
//    Mat R = Mat(3,2, CV_8UC3);
//    randu(R, Scalar::all(0), Scalar::all(255));
//    cout << "R =" << endl << "" << R << endl << endl;
    
    // Code4
//    Mat img = imread("148_.jpg");
//    Mat grey;
//    cvtColor(img, grey, COLOR_BGR2GRAY);
//    Mat sobelx;
//    Sobel(grey, sobelx, CV_32F, 1, 0);
//    double minVal, maxVal;
//    minMaxLoc(sobelx, &minVal, &maxVal);
//    Mat draw;
//    sobelx.convertTo(draw, CV_8U, 255.0/(maxVal - minVal), -minVal * 255.0/(maxVal - minVal));
//    namedWindow("image", WINDOW_AUTOSIZE);
//    imshow("image", draw);
//    waitKey();
    
    // Code5 合并图像
//    double alpha = 0.5;
//    double beta;
//    double input;
//    Mat src1, src2, dst;
//    cout << " Simple linear Blender" << endl;
//    cout << "----------------------" << endl;
//    cout << "* Enter alpha [0-1]:";
//    cin >> input;
//    if (input >= 0 && input <= 1) {
//        alpha = input;
//    }
//    src1 = imread("491_.jpg");
//    src2 = imread("109_.jpg");
//    if (src1.empty()) {
//        cout << "error loading src1" << endl;
//        return -1;
//    }
//    if (src2.empty()) {
//        cout << "error loading src2" << endl;
//        return  -1;
//    }
//    beta = (1.0 - alpha);
//    addWeighted(src1, alpha, src2, beta, 0.0, dst);
//    imshow("liner Blend", dst);
//    waitKey(0);
//    return 0;
//    
//    // Code6  对比度和亮度
//    double alpha = 1.0;
//    int beta = 0;
//    String imageName("IMG_7774.JPG");
//    if (argc > 1) {
//        imageName = argv[1];
//    }
//    Mat image = imread( imageName );
//    Mat new_image = Mat::zeros(image.size(), image.type() );
//    cout << " Basic Linear Transforms " << endl;
//    cout << "--------------------------" << endl;
//    cout << "* Enter the alpha Value [1.0 - 3.0]:";
//    cin >> alpha;
//    cout << "* Enter the beta Value [0 - 100]:";
//    cin >> beta;
//    for (int y = 0; y< image.rows; y++) {
//        for (int x = 0; x < image.cols; x ++) {
//            for (int c = 0; c < 3 ; c++) {
//                new_image.at<Vec3b>(y, x)[c]  = saturate_cast<uchar>(alpha *(image.at<Vec3b>(y,x)[c]) + beta);
//            }
//        }
//    }
//    namedWindow("Original Image", WINDOW_AUTOSIZE);
//    namedWindow("New Image",WINDOW_AUTOSIZE);
//    imshow("Original Image", image);
//    imshow("New Image", new_image);
//    waitKey();
//    return 0;
//    
//}

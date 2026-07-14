#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

std::string windowName = "Resize Image";
int scaleFactor = 50, maxScale = 100;
int typeScale = 0, maxTypeScale = 1;
Mat img, rescaleImage;

void rescale(int, void *){

    double scaleFactorDouble;
    if (typeScale == 1){
        scaleFactorDouble = 1 + scaleFactor/100.0;
    }else{
        scaleFactorDouble = scaleFactor/100.0;
    }
    
    if (scaleFactorDouble == 0){
        scaleFactorDouble = 1;
    }
    
    resize(img, rescaleImage, Size(), scaleFactorDouble, scaleFactorDouble, INTER_LINEAR);
    imshow(windowName, rescaleImage);
}


int main()
{
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_ERROR);
    img = imread("../../bird.jpg", IMREAD_COLOR_BGR);
    
    namedWindow(windowName, WINDOW_AUTOSIZE);
    createTrackbar("Scale", windowName, &scaleFactor, maxScale, rescale);
    createTrackbar("TypeScale", windowName, &typeScale, maxTypeScale, rescale);

    rescale(25,0);

    int k = 0;
    while(k!=27)
    {
        k= waitKey(20) & 0xFF;
    }

    destroyAllWindows();
    return 0;
}
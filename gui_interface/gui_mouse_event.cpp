#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
Point left, right;
Mat img;

void drawRect(int action, int x, int y, int flags, void * userdata){
    if( action == EVENT_LBUTTONDOWN ){
        left = Point(x, y);
    }

    else if (action == EVENT_LBUTTONUP){
        right = Point(x, y);
        rectangle(img, left, right, (255, 0, 0), 2);

        //Crop and save the image
        int x1 = std::min(left.x, right.x);
        int y1 = std::min(left.y, right.y);
        int x2 = std::max(left.x, right.x);
        int y2 = std::max(left.y, right.y);

        Rect roi(x1, y1, x2 - x1, y2 - y1);
        std::cout << "ROI : " << roi.x << " " << roi.y << " " << roi.width << " " << roi.height << std::endl;
        std::cout << "Image : " << img.cols << " x " << img.rows << '\n';

        roi &= Rect(0,0, img.cols, img.rows);
        
        if (roi.width > 0 && roi.height > 0) {
            cv::Mat crop = img(roi);
            bool ok = cv::imwrite("../../crop.jpg", crop);

            std::cout << "Sauvegarde : " << ok << std::endl;
        }
    }
}


int main()
{
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_ERROR);
    img = imread("../../bird.jpg", IMREAD_COLOR_BGR);
    Mat dummy = img.clone();

    namedWindow("Crop");
    setMouseCallback("Crop", drawRect);

    int k = 0;
    // loop until escape character is pressed
    while(k!=27)
    {
        imshow("Crop", img);
        putText(img,"Choose Left and right corner, Press ESC to exit and c to clear" , Point(10,30), FONT_HERSHEY_SIMPLEX, 0.7,Scalar(255,255,255), 2 );
        k= waitKey(20) & 0xFF;
        if(k == 99){
            dummy.copyTo(img);
        }
    }
    return 0;
}
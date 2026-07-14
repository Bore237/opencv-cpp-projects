#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    cv::VideoCapture cap(0);

    if (!cap.isOpened()) {
        std::cerr << "Impossible d'ouvrir la webcam" << std::endl;
        return -1;
    }

    cv::Mat frame;
    int key = 0; 
    cv::Mat gray;
    
    enum Mode{
        NORMAL,
        NEGATIF,
        GRAYSCALE
    };

    Mode mode = NORMAL;

    while(true){
        cap >> frame; //recuperer image

        if (frame.empty()){
            std::cerr << "Image vide reçue" << std::endl;
            break;
        }

        key = cv::waitKey(255);
        if (key == 110){
            mode = NEGATIF;
        }else if (key == 103){
            mode = GRAYSCALE;
        }else if (key == 100){
            mode = NORMAL;
        }
        
        switch (mode){
            case NEGATIF:
                cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
                gray = 255 - gray;
                cv::putText(gray, "Negatif mode", cv::Point(20, 50), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255), 3);
                cv::imshow("Frame", gray);
                break;
            
            case GRAYSCALE:
                cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
                cv::rectangle(gray, cv::Point(10, 10), cv::Point(280, 70), cv::Scalar(0), -1);
                cv::putText(gray, "GrayScale mode", cv::Point(20, 50), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255), 3);
                cv::imshow("Frame", gray);
                break;
            
            default:
                cv::putText(frame, "Normal mode", cv::Point(20, 50), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 0, 0), 3);
                cv::imshow("Frame", frame);
                break;
        }

        if (key == 27){
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
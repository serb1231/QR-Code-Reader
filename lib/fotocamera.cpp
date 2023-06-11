#include <fotocamera.hpp>

fotocamera::fotocamera(){

    this->image =cv::Mat();
}

void fotocamera::InitWebcam(){
    this->cam =cv::VideoCapture(0);
}

bool fotocamera::checkOpenWebcam(){
    return this->cam.isOpened();
}

bool fotocamera::TakeFoto(){
    return this->cam.read(this->image);
    
}

void fotocamera::OpenFoto(){
    cv::imshow("Photo", this->image);
}


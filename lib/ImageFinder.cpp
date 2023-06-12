#include "ImageFinder.hpp"


ImageFinder::ImageFinder(){
    this->path ="";
}

void ImageFinder::Setpath(std::string path){
    this->path=path;
}


bool ImageFinder::CheckPathforImage(std::string InputPath){
    this->image = cv::imread(InputPath);
    if (this->image.empty()) {
        std::cout << "Path incorrect: " << InputPath << std::endl;
        return false;
    }
    return true;
}

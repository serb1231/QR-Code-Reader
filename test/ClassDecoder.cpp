#include <Decoder.hpp>
#include <stdio.h>

int main(){

    auto dec = Decoder();
    std::string data;

    cv::Mat image = cv::imread("../test_images/tractor-school-qr-code.png");
    data = dec.decode(image);
    std::cout << data << std::endl;

    return 0;

}


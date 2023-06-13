#include <Decoder.hpp>
#include <stdio.h>

int main(){

    auto dec = Decoder();
    std::string data;

    cv::Mat image = cv::imread("../../test_images/QR_Code_Foto_Technopedia.jpg");
    data = dec.decode(image);
    std::cout << data << std::endl;

    return 0;

}


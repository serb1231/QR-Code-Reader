#include <Decoder.hpp>
#include <stdio.h>

int main(){

    auto dec = Decoder();

    cv::Mat image = cv::imread("../../QR_Code_Foto_Technopedia.jpg");
    int err = dec.decode(image);

    return err;

}


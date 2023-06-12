#include <Decoder.hpp>
#include <stdio.h>

int main(){

    auto dec = Decoder();

    cv::Mat image = cv::imread("../../../../U.jpg");
    int err = dec.decode(image);

    return err;

}


#include <Decoder.hpp>
#include <stdio.h>

int main(){

    auto dec = Decoder();

    cv::Mat image = cv::imread("/mnt/c/Users/mario/TU/TU_Semester_8_OTTO/Prog_CPP/GroupNProject/QR_Code_Foto_Technopedia.jpg");
    int err = dec.decode(image);

    return err;

}


#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>

/// This class contains all the functionality to actually decode the QR-Code

class Decoder{
    public:

    int decode(cv::Mat QRimage);

};

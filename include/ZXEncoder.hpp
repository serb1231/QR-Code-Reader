#pragma once

#include <iostream>
#include <stdio.h>
#include <string.h>

/// This class contains all the functionality to actually decode the QR-Code

class ZX_Encoder
{
public:
    std::string encode_text_QRcode(std::string text, std::string file_name, std::string path, int size, int margin);
};

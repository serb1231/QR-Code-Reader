#include <ZXEncoder.hpp>

#include <ZXing/BarcodeFormat.h>
#include <ZXing/BitMatrix.h>
#include <ZXing/BitMatrixIO.h>
#include <ZXing/CharacterSet.h>
#include <ZXing/MultiFormatWriter.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace ZXing;

std::string getFileType(std::string file_name)
{
    char* file_type=".";
    int file_type_start_pos;

    file_type_start_pos = file_name.rfind(".");
    file_name.copy(file_type,4, file_type_start_pos);
    return file_type;
}

int ZX_Encoder::encode_text_QRcode(std::string text, std::string file_name, std::string path, int size, int margin)
{
    std::cout << "encoding..."
              << "\n";
    if (text.empty())
    {
        std::cout << "ERROR: Passed text is empty." << std::endl;
        return -1;
    }
    if (file_name.empty())
    {
        std::cout << "ERROR: Passed file name is empty." << std::endl;
        return -1;
    }
    else if (file_name.find(".jpg") == 0 || file_name.find(".jpeg") == 0 || file_name.find(".png") == 0)
    {
        std::cout << "ERROR: Passed file name doesn't have a file type. Supported formats are .jpg and .png." << std::endl;
        return -1;
    }
    std::cout << file_name << "\n";

    std::cout << file_name.find(".jpeg") << "\n";

    // if (file_name.find(".jpeg") != 0)
    // {
    //     file_name.replace(file_name.find(".jpeg"), 5, ".jpg");
    // }

    if (path.empty())
    {
        std::cout << "INFO: Passed path is empty. The image will be written in the default path." << std::endl;
        path = "./";
    }
    if (size < 11)
    {
        std::cout << "ERROR: Passed size is too small. The size should be >10." << std::endl;
    }
    else if (size < 100)
    {
        std::cout << "WARNING: Passed size is small. Depending on the input, the resulting image might be larger than specified." << std::endl;
    }
    if (margin < 0)
    {
        std::cout << "WARNING: Passed margin is negativ. It will be discraded" << std::endl;
        margin = 0;
    }

    std::cout << "requirements checked..." << "\n";

    BarcodeFormat code_type = BarcodeFormatFromString("QRCode");
    CharacterSet encoding = CharacterSetFromString("UTF8");
    int ecc_level = 1;
    auto writer = MultiFormatWriter(code_type).setMargin(margin).setEncoding(encoding).setEccLevel(ecc_level);

    // this returns a sort of array where each bit represents a pixel and it can be black (1) or white (0):
    BitMatrix bit_matrix = writer.encode(text, size, size);

    // therefore we need to convert the BitMatrix into a real image:
    // this maps the bits to uint8, so 0...255:
    auto bitmap = ToMatrix<uint8_t>(bit_matrix);

    bool success = false;

    if (file_name.find(".jpg") != 0)
    {
        success = stbi_write_jpg(path.append(file_name).c_str(), bitmap.width(), bitmap.height(), 1, bitmap.data(), 0);
    }
    else if (file_name.find(".png") != 0)
    {
        success = stbi_write_png(path.append(file_name).c_str(), bitmap.width(), bitmap.height(), 1, bitmap.data(), 0);
    }

    if (!success)
    {
        std::cerr << "Failed to write image: " << file_name << " to " << path << std::endl;
        return -1;
    }
    return 0;
}
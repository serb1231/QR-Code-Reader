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
#include <filesystem>

using namespace ZXing;

std::string getFileType(std::string file_name)
{
    char *file_type = ".";
    int file_type_start_pos;

    file_type_start_pos = file_name.rfind(".");
    file_name.copy(file_type, 4, file_type_start_pos);
    return file_type;
}

std::string ZX_Encoder::encode_text_QRcode(std::string text, std::string file_name, std::string path, int size, int margin)
{
    std::cout << "Encoding started..." << std::endl;
    if (text.empty())
    {
        return "ERROR: Passed text is empty.";
    }
    if (file_name.empty())
    {
        return "ERROR: Passed file name is empty.";
    }

    if(file_name.length()>=5){
        std::string last5char = file_name.substr(file_name.length()-5);
        std::string last4char = file_name.substr(file_name.length()-4);

         if (last4char.find(".jpg") == std::string::npos && last5char.find(".jpeg") == std::string::npos && last4char.find(".png") == std::string::npos)
        {
            return "ERROR: Passed file name doesn't have a file type. Supported formats are .jpg, .jpeg and .png.";
        }
    }else{

        return "ERROR: Passed file name doesn't have a file type. Supported formats are .jpg, .jpeg and .png.";
    }

   
    std::cout << "Filename: " + file_name << std::endl;
    std::cout << "Text to encode: "+ text <<std::endl;

    if (path.empty())
    {
        std::cout << "INFO: Passed path is empty. The image will be written in the default path." << std::endl;
        path = "./";
    }
    if (std::filesystem::exists(path)==0){
        return "ERROR: Passed filepath does not exist.";
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

    if (file_name.find(".jpg") != std::string::npos || file_name.find(".jpeg") != std::string::npos)
    {
        success = stbi_write_jpg(path.append(file_name).c_str(), bitmap.width(), bitmap.height(), 1, bitmap.data(), 0);
    }
    else if (file_name.find(".png") != std::string::npos)
    {
        success = stbi_write_png(path.append(file_name).c_str(), bitmap.width(), bitmap.height(), 1, bitmap.data(), 0);
    }

    if (!success)
    {
        return "Failed to write image: " + file_name + " to " + path;
    }
    return "Image created successfully!\n";
}
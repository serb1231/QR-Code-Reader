#include <Decoder.hpp>
#include <opencv2/opencv.hpp>

int Decoder::decode(cv::Mat QRimage){

// Check if the image was successfully loaded
    if (QRimage.empty()) {
        std::cout << "Failed to load the image." << std::endl;
        return -1;
    }

    // Convert image to binary image
    cv::Mat binaryImage;
    cv::threshold(QRimage, binaryImage, 128, 255, cv::THRESH_BINARY);

        
    // Define the desired width and height for the resized image
    int newWidth = 250;
    int newHeight = 250;

    // Create a resized image using the defined width and height
    cv::Mat resizedImage;
    cv::resize(binaryImage, resizedImage, cv::Size(newWidth, newHeight));

    std::cout << "Image successfully resized." << std::endl;

    // Display the original image and the sharpened image
    cv::imshow("Original Image", QRimage);
    cv::imshow("Binary Image", resizedImage);
    cv::waitKey(0);


    // Detect and decode the QR cod
    std::vector<cv::Point> points;  // Stores the corner points of the QR code
    cv::QRCodeDetector qrDecoder;
    std::string data = qrDecoder.detectAndDecode(resizedImage, points);
    if (!data.empty())
    {
        // QR code detected and decoded successfully
        std::cout << "Decoded data: " << data << std::endl;

        // Display the result
        cv::drawContours(resizedImage, std::vector<std::vector<cv::Point>>{points}, -1, cv::Scalar(0, 255, 0), 2);
        cv::imshow("QR Code", resizedImage);
        cv::waitKey(0);
        return 0;
    }
    else
    {
        // QR code not detected or decoding failed
        std::cout << "QR code not found or decoding failed" << std::endl;
        return -1;
    }

}
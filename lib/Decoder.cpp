#include <Decoder.hpp>
#include <opencv2/opencv.hpp>

int Decoder::decode(cv::Mat QRimage){

    /// Check if the image was successfully loaded
    if (QRimage.empty()) {
        std::cout << "Failed to load the image." << std::endl;
        return -1;
    }

    /// Check if image is in size range
    int width = QRimage.cols;
    int height = QRimage.rows;

    /// Too small images can't be decoded
    if(width < 199 || height < 199){
        std::cout << "Image too small, please upload a bigger image." << std::endl;
        return -1;
    }

    /// crop Image if code is detected
    /// Create a QR code detector object
    cv::QRCodeDetector qrDetector;

    /// Define a vector to store the output points of the detected quadrangle
    std::vector<cv::Point> points;
    
    /// Detect the QR code and obtain the quadrangle points
    bool detectionResult = qrDetector.detect(QRimage, points);

    
    std::cout << "Points: " << points << std::endl;

    cv::Mat croppedImage;

    if (detectionResult) {
        /// Draw the quadrangle on the image
        cv::polylines(QRimage, points, true, cv::Scalar(0, 255, 0), 2);

        cv::Rect roi(points[0], points[2]);

        /// Crop the image using the ROI
        croppedImage = QRimage(roi);

        /// Display the cropped image
        cv::imshow("Cropped Image", croppedImage);

        /// Display the image with the detected QR code
        cv::imshow("Detected QR Code", QRimage);
        cv::waitKey(0);

    } else {
        std::cout << "No QR code detected!" << std::endl;
    }

    /// Check if image is in size range
    width = croppedImage.cols;
    height = croppedImage.rows;

    /// Image too big, resize it to 500x500
    while(width > 500 || height > 500)
    {
        width *= 0.9;
        height *= 0.9;
        cv::resize(croppedImage, croppedImage, cv::Size(width, height));
    }

    std::cout << "Image successfully resized." << std::endl;

    /// Convert image to binary image
    cv::Mat binaryImage;
    cv::threshold(croppedImage, binaryImage, 128, 255, cv::THRESH_BINARY);

    /// Detect and decode the QR cod
    //std::vector<cv::Point> points;  /// Stores the corner points of the QR code
    cv::QRCodeDetector qrDecoder;
    std::string data = qrDecoder.detectAndDecode(binaryImage, points);
    if (!data.empty())
    {
        /// QR code detected and decoded successfully
        std::cout << "Decoded data: " << data << std::endl;

        /// Display the result
        cv::drawContours(binaryImage, std::vector<std::vector<cv::Point>>{points}, -1, cv::Scalar(0, 255, 0), 2);
        cv::imshow("QR Code", binaryImage);
        cv::waitKey(0);
        return 0;
    }
    else
    {
        /// QR code not detected or decoding failed
        std::cout << "QR code not found or decoding failed" << std::endl;
        return -1;
    }

}
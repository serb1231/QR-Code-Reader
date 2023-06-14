#include <Decoder.hpp>
#include <opencv2/opencv.hpp>
#include <QualityImprove.hpp>

std::string Decoder::decode(cv::Mat QRimage)
{

    /// Check if the image was successfully loaded
    if (QRimage.empty())
    {
        std::cout << "Failed to load the image." << std::endl;
        return "No Image";
    }

    /// Check if image is in size range
    int width = QRimage.cols;
    int height = QRimage.rows;

    /// Too small images can't be decoded
    if (width < 199 || height < 199)
    {
        std::cout << "Image too small, please upload a bigger image." << std::endl;
        return "Image too small";
    }
    cv::Mat initialImage = QRimage.clone();
    std::string data;
    
for(double alpha = 0.5; alpha <= 2; alpha += 0.5) {
        for(int beta = -100; beta <= 100; beta += 20) {

    QRimage = ContrastBrightnessChange(initialImage, alpha, beta);
    // apply a process to make the edges sharper
    QRimage = sharperImage(QRimage);

    /// crop Image if code is detected
    /// Create a QR code detector object
    cv::QRCodeDetector qrDetector;

    /// Define a vector to store the output corner points of the detected Region
    std::vector<cv::Point> points;

    /// Detect the QR code and obtain the Region corner points
    bool detectionResult = qrDetector.detect(QRimage, points);

    cv::Mat croppedImage = QRimage;

    if (detectionResult)
    {
        /// Draw the quadrangle on the image
        cv::polylines(QRimage, points, true, cv::Scalar(0, 255, 0), 2);

        cv::Rect roi(points[0], points[2]);

        /// Crop the image using the ROI
        croppedImage = QRimage(roi);
    }
    else
    {
        return "No QR code detected!";
    }

    /// Check if image is still in size range
    width = croppedImage.cols;
    height = croppedImage.rows;

    /// Image too big, resize it to ~500x500
    while (width > 500 || height > 500)
    {
        width *= 0.9;
        height *= 0.9;
        cv::resize(croppedImage, croppedImage, cv::Size(width, height));
    }

    /// Convert image to binary image
    cv::Mat binaryImage;
    cv::threshold(croppedImage, binaryImage, 128, 255, cv::THRESH_BINARY);

    /// Detect and decode the QR code
    cv::QRCodeDetector qrDecoder;
    std::string data = qrDecoder.detectAndDecode(binaryImage, points);

    if (!data.empty())
    {
        /// QR code detected and decoded successfully
        return data;
    }
    // else
    // {   
    //     /// QR code not detected or decoding failed
    //     std::cout << "QR code not found or decoding failed" << std::endl;
    // }


        }
}
        
        return "No QR-Code";

}

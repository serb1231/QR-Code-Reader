#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/photo.hpp>
#include <iostream>
#include <dirent.h>
#include <sys/types.h>

// This function just takes a vector of noisy images, and denoises them
cv::Mat DenoiseFromObservations(const std::vector<cv::Mat> &observations, cv::Mat &result)
{
    double lambda = 1.0; // by default
    int niters = 30;     // by default
    cv::denoise_TVL1(observations, result, lambda, niters);
    return result;
}

cv::Mat add_noiseLittle(cv::Mat &img)
{
    std::cout << "image channels, bafore noise " << img.channels() << std::endl;
    cv::Mat noise(img.size(), img.type());
    if (img.channels() == 1)
    {
        cv::Scalar m(10);
        cv::Scalar sigma(1);
        cv::randn(noise, m, sigma);
    }
    else
    {
        cv::Scalar m(10, 12, 34);
        cv::Scalar sigma(1, 5, 50);
        cv::randn(noise, m, sigma);
    }

    cv::Mat imgCopy = img.clone();
    imgCopy += noise;
    imgCopy = cv::min(imgCopy, 255);
    imgCopy = cv::max(imgCopy, 0);
    return imgCopy;
}
cv::Mat add_noiseLot(cv::Mat &img)
{
    std::cout << "image channels, bafore noise " << img.channels() << std::endl;
    cv::Mat noise(img.size(), img.type());
    if (img.channels() == 1)
    {
        cv::Scalar m(0);
        cv::Scalar sigma(25); // Increased sigma value for greater noise variation
        cv::randn(noise, m, sigma);
    }
    else
    {
        cv::Scalar m(0, 0, 0);
        cv::Scalar sigma(25, 25, 25); // Increased sigma value for greater noise variation
        cv::randn(noise, m, sigma);
    }

    cv::Mat imgCopy = img.clone();
    imgCopy += noise;
    imgCopy = cv::min(imgCopy, 255);
    imgCopy = cv::max(imgCopy, 0);
    return imgCopy;
}

void DenoiseTakeFromFolder(char *path)
{
    DIR *dr;
    struct dirent *en;
    std::vector<cv::Mat> BlurryImg;
    dr = opendir(path);

    if (dr)
    {
        int imgCount = 0;
        while ((en = readdir(dr)) != NULL)
        {
            if (strcmp(en->d_name, ".") != 0 && strcmp(en->d_name, "..") != 0)
            {
                std::string fileName = en->d_name;
                std::string pathString = path;
                std::string pathToFile = pathString + fileName;
                cv::Mat img = cv::imread(pathToFile, cv::IMREAD_GRAYSCALE);
                if (img.empty())
                {
                    std::cout << "Could not open or find the image" << std::endl;
                    return;
                }
                std::cout << "../test_images/SameImageBlurry/" + fileName << " " << img.cols << " " << img.rows << " " << img.channels() << std::endl;
                imgCount++; // Increment the counter
                BlurryImg.push_back(img);
            }
        }
        closedir(dr);
        cv::waitKey();
    }
    cv::Mat result;
    cv::denoise_TVL1(BlurryImg, result, 1.0, 30);
    cv::imwrite("denoised_image.jpg", result);
}

void TestNoiseSameImageAndDenoise(std::string path)
{
    cv::Mat img = cv::imread(path, cv::IMREAD_GRAYSCALE);
    if (img.empty())
    {
        std::cout << "Could not open or find the image" << std::endl;
        return;
    }
    cv::Mat noisyImg1 = add_noiseLittle(img);
    cv::Mat noisyImg2 = add_noiseLot(img);
    cv::imshow("first noisy image", noisyImg1);
    cv::imshow("second noisy image", noisyImg2);
    std::vector<cv::Mat> etc;
    etc.push_back(noisyImg1);
    etc.push_back(noisyImg2);
    double lambda = 1.0; // by default
    int niters = 30;     // by default
    cv::Mat result;
    cv::denoise_TVL1(etc, result, lambda, niters);
    cv::imshow("Resulting", result);
    cv::waitKey();
}

int main()
{
    // load image
    // cv::Mat img = cv::imread("../test_images/QR_another_real_test_foto_2.jpg", cv::IMREAD_COLOR);
    // if (img.empty()) {
    //     std::cout << "Could not open or find the image" << std::endl;
    //     return -1;
    // }

    // // create a simple 3x3 kernel
    // cv::Mat kernel = (cv::Mat_<float>(3,3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);

    // // perform deconvolution
    // cv::Mat result = deconvolve(img, kernel);

    // This gave a sharper image as a result
    // cv::Mat result_detailEnhance;
    // detailEnhance(img,result_detailEnhance, 10,0.15f);
    // cv::imshow("Detail Enhances Image", result_detailEnhance);

    // this would be good only for specific values
    // we could iterate over them, and try to detect the QR code
    // afterwards
    // cv::Mat result_conversion;
    // img.convertTo(result_conversion,-1,1,-100);
    // cv::imshow("Conversion Image", result_conversion);
    // cv::waitKey();

    // no cuda support; the library needs cuda support for this
    // cv::Mat result_denoise;
    // cv::cuda::fastNlMeansDenoising(img, result_denoise,1,21,7,cv::cuda::Stream::Null());
    // cv::imshow("Denoise Image", result_denoise);
    // cv::waitKey();

    DenoiseTakeFromFolder("../test_images/SameImageBlurry/");
    TestNoiseSameImageAndDenoise("../test_images/SameImageBlurry/WhatsApp Image 2023-06-11 at 7.10.18 PM.jpeg");

    return 0;
}
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

// This function adds noise to one image
cv::Mat add_noise(cv::Mat&img, bool aLot) {
    std::cout<<"image channels, bafore noise "<<img.channels()<<std::endl;
    cv::Mat noise(img.size(),img.type());
    if(aLot == false){
        if(img.channels() == 1) {
            cv::Scalar m(10);
            cv::Scalar sigma(1);
            cv::randn(noise, m, sigma);
        }
        else {
            cv::Scalar m(10, 12, 34);
            cv::Scalar sigma(1, 5, 50);
            cv::randn(noise, m, sigma);
        }
    }
    else {
        if(img.channels() == 1) {
            cv::Scalar m(0);
            cv::Scalar sigma(25); // Increased sigma for greater noise variation
            cv::randn(noise, m, sigma);
        }
        else {
            cv::Scalar m(0, 0, 0);
            cv::Scalar sigma(25, 25, 25); // Increased sigma for greater noise variation
            cv::randn(noise, m, sigma);
    }
    }

    cv::Mat imgCopy = img.clone();
    imgCopy += noise;
    imgCopy = cv::min(imgCopy, 255);
    imgCopy = cv::max(imgCopy, 0);
    return imgCopy;
}

// this function takes the path to a folder
// containing image with different types of noise
// and creates a new image based on them
cv::Mat DenoiseTakeFromFolder(char* path, bool isGrayScale) {
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
                }else{
                imgCount++;
                BlurryImg.push_back(img);
                }
            }
        }
        closedir(dr);
    }
        cv::Mat result;
        cv::denoise_TVL1(BlurryImg, result, 1.0, 30);
        return result;
}


// A test for adding noise to the same image, and then denoise them
cv::Mat TestNoiseSameImageAndDenoise(std::string path) {
    cv::Mat img = cv::imread(path, cv::IMREAD_GRAYSCALE);
    if (img.empty()) {
    std::cout << "Could not open or find the image" << std::endl;
    return cv::Mat();
}
    cv::Mat noisyImg1 = add_noise(img, false);
    cv::Mat noisyImg2 = add_noise(img, true);
    cv::imshow("first noisy image",noisyImg1);
    cv::imshow("second noisy image",noisyImg2);
    std::vector<cv::Mat> etc;
    etc.push_back(noisyImg1);
    etc.push_back(noisyImg2);
    double lambda = 1.0; // by default
    int niters = 30;     // by default
    cv::Mat result;
    cv::denoise_TVL1(etc, result, lambda, niters);
    return result;
}

// perform operation on image to enhance sharp edges
cv::Mat sharperImage(cv::Mat img) {
    if (img.empty()) {
        std::cerr << "We were passed an empty image; we returned an empty object" << std::endl;
        return cv::Mat();
    }

    // Check the image depth and number of channels
    if (img.depth() != CV_8U || img.channels() > 4) {
        std::cerr << "The image depth should be CV_8U and number of channels less than 5." << std::endl;
        return cv::Mat();
    }
    cv::Mat result_detailEnhance;
    detailEnhance(img,result_detailEnhance, 10,0.15f);
    return result_detailEnhance;
}

// change the brightness and contrast of an image
// this could be used for hyperparameter detection as well, testing more alpha and beta
cv::Mat ContrastBrightnessChange(cv::Mat img, double alpha, int beta) {

    if (img.empty()) {
    std::cerr << "We were passed an empty image; we returned an empty object" << std::endl;
    return cv::Mat();
    }
    // Check the image depth and number of channels
    if (img.depth() != CV_8U || img.channels() > 4) {
        std::cerr << "The image depth should be CV_8U and number of channels less than 5." << std::endl;
        return cv::Mat();
    }

    cv::Mat new_img = cv::Mat::zeros( img.size(), img.type() );
    if (new_img.empty()) {
    std::cerr << "Could not create new image" << std::endl;
    return cv::Mat();
    }

    for( int y = 0; y < img.rows; y++ ) {
        for( int x = 0; x < img.cols; x++ ) {
            for( int c = 0; c < img.channels(); c++ ) {
                new_img.at<cv::Vec3b>(y,x)[c] =
                  cv::saturate_cast<uchar>( alpha*img.at<cv::Vec3b>(y,x)[c] + beta );
            }
        }
    }
    return new_img;
}

// cv::Mat HyperParameterDetectionContrastBrightness(cv::Mat img) {
//     cv::Mat result;
//     for(int alpha = 0.5;alpha<=1.5;alpha+=0.1) {
//         for(int beta = -100;beta<=100; beta+=20)
//             ContrastBrightnessChange(img, alpha, beta);
//     }
// }

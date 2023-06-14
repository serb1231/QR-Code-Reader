#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/photo.hpp>
#include <iostream>
#include <dirent.h>
#include <sys/types.h>
cv::Mat DenoiseFromObservations (const std::vector<cv::Mat>& observations, cv::Mat& result);
cv::Mat add_noise(cv::Mat&img, bool aLot);
cv::Mat DenoiseTakeFromFolder(char* path_ini, bool isGrayScale);
cv::Mat TestNoiseSameImageAndDenoise(std::string path);
cv::Mat sharperImage(cv::Mat img);
cv::Mat ContrastBrightnessChange(cv::Mat img, double alpha, int beta);
cv::Mat HyperParameterDetectionContrastBrightness(cv::Mat img);
#pragma once

#include <iostream>
#include <string>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <filesystem>

/// pahtfinder Class
/**
   This Class prints checks if a path is viable and opens the picture
 **/
struct ImageFinder {
  std::string path;
  cv::Mat image;
  /// Constructor of imagefinder
  ImageFinder();
  ///Input path
  void Setpath(std::string path);
  /// Input path for user
  bool CheckPathforImage(std::string InputPath);
};

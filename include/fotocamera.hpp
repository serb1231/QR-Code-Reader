#pragma once

#include <iostream>
#include <string>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <tgmath.h>

/// fotocamera Class
/**
   This Class connects to the camera, takes pictures and saves them
 **/
struct fotocamera {
  cv::VideoCapture cam;
  cv::Mat image;
  /// Constructor of fotocamera
  fotocamera();
  ///Input path
  void InitWebcam();
  /// Input path for user
  bool checkOpenWebcam();
  /// Checks if a path is correct 
  bool TakeFoto();
  /// Opens a Picture
  void OpenFoto();
};

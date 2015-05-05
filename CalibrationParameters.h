//
// Created by Adam Morris on 4/29/15.
//

#pragma once

#include <string>

#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>

class CalibrationParameters {
public:
    cv::Mat intrincsicMatrix = cv::Mat::zeros(3, 3, CV_32F);
    cv::Mat distCoeffs = cv::Mat::zeros(1, 5, CV_32F);

    CalibrationParameters(std::string parameterFilePath);
    ~CalibrationParameters();
};

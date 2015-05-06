//
// Created by Adam Morris on 4/29/15.
//

#include "CalibrationParameters.h"

CalibrationParameters::CalibrationParameters(std::string parameterFilePath) {
    this->intrincsicMatrix = cv::Mat::zeros(3, 3, CV_32F);
    this->distCoeffs = cv::Mat::zeros(1, 5, CV_32F);

    cv::FileStorage fs(parameterFilePath, cv::FileStorage::READ);

    fs["intrinsic_matrix"] >> intrincsicMatrix;
    fs["dist_coeffs"] >> distCoeffs;

    fs.release();

    std::cout << std::endl << "Loaded camera calibration parameters." << std::endl;
    std::cout << "\tIntrincsic Matrix: " << intrincsicMatrix << std::endl;
    std::cout << "\tDistortion Coefficients: " << distCoeffs << std::endl << std::endl;
}

CalibrationParameters::~CalibrationParameters() {
    intrincsicMatrix.release();
    distCoeffs.release();
}

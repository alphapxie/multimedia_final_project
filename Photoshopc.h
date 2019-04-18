//
// Created by victo on 18/04/2019.
//
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

#ifndef MULTIMEDIA_FINAL_PROJECT_PHOTOSHOPC_H
#define MULTIMEDIA_FINAL_PROJECT_PHOTOSHOPC_H

using namespace cv;

class Photoshopc {
    Mat image;
public:
    Photoshopc();
    Mat dilatation(int);
    Mat erosion(int);
    Mat resize();
    Mat luminosity();
    Mat panorama();
    Mat stitching();
    Mat cannyEdgeDetection(double, double, int);

};


#endif //MULTIMEDIA_FINAL_PROJECT_PHOTOSHOPC_H

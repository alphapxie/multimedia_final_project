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
using namespace std;

class Photoshopc {
    Mat image;
public:
    Photoshopc(String*);
    Photoshopc(int, int);
    Mat dilatation(int);
    Mat erosion(int);
    Mat resize(double, double);
    Mat luminosity(int);
    Mat panorama(vector<Mat>*);
    Mat cannyEdgeDetection(double, double, int);

};


#endif //MULTIMEDIA_FINAL_PROJECT_PHOTOSHOPC_H

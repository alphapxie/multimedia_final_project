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
    Mat src;
    Mat image;
    Mat newImage;
public:
    Photoshopc(String*);
    Photoshopc(int, int);
    Photoshopc(Mat);
    void dilatation(int);
    void erosion(int);
    void resize(double, double);
    void luminosity(int);
    void panorama(vector<Mat>*);
    void cannyEdgeDetection(double, double, int);
    Mat* getImage();
    Mat* getNewImage();
    void save();
    void reset();

};


#endif //MULTIMEDIA_FINAL_PROJECT_PHOTOSHOPC_H

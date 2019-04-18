//
// Created by victo on 18/04/2019.
//
#include <opencv2/opencv.hpp>
#ifndef MULTIMEDIA_FINAL_PROJECT_PHOTOSHOPC_H
#define MULTIMEDIA_FINAL_PROJECT_PHOTOSHOPC_H

using namespace cv;
using namespace std;

class Photoshopc {
    Mat image;
public:
    Photoshopc(String*);
    Photoshopc(int, int);
    Mat morphologicalOperators();
    Mat erosion();
    Mat resize();
    Mat luminosity(int);
    Mat panorama(vector<Mat>*);
    Mat cannyEdgeDetection();

};


#endif //MULTIMEDIA_FINAL_PROJECT_PHOTOSHOPC_H

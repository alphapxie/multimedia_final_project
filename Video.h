//
// Created by Grégoire on 18/04/2019.
//

#ifndef MULTIMEDIA_FINAL_PROJECT_VIDEO_H
#define MULTIMEDIA_FINAL_PROJECT_VIDEO_H
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


class Video {
    VideoCapture video;
public:
    Mat brightness(int);
    Mat Gaussian(int, int);

};


#endif //MULTIMEDIA_FINAL_PROJECT_VIDEO_H

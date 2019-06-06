//
// Created by victo on 05/06/2019.
//
#include <iostream>

#include <opencv2/opencv.hpp>
#include "cvui-master/cvui-master/cvui.h"
#include "FileReader.h"
#include "Photoshopc.h"
#include "FaceDetection.h"

using namespace std;
using namespace cvui;

#define WINDOWS "windows"
#ifndef MULTIMEDIA_FINAL_PROJECT_GUI_H
#define MULTIMEDIA_FINAL_PROJECT_GUI_H


class Gui {
    map<string, vector<int>> values = {
            {"dilation",           {0}},
            {"erosion",            {0}},
            {"cannyEdgeDetection", {0, 0, 3}},
            {"luminosity",         {0}},
            {"resize",             {100, 100}}
    };
    const char * videoType[2] = {"*.mp4", ".avi"};
    const char * imageType[2] = {"*.jpg", "*.png"};
    bool facialRecognition = false;
    Mat frame, temp;
    int currentOption = 0;
    Photoshopc photoshopObject = Photoshopc(1, 1);
    bool isVideo = true;

    void setOption();
    void showParameters(bool hasOption);
    void updateImage();
    void resetImage();
    void addImage(cv::Mat * image);
    int showInterface(int type);
    int startMenu();
public:
    void startGui();

    };


#endif //MULTIMEDIA_FINAL_PROJECT_GUI_H

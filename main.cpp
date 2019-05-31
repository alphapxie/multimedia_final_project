#include <iostream>

#define CVUI_IMPLEMENTATION

#include <opencv2/opencv.hpp>
#include "cvui-master/cvui-master/cvui.h"
#include "tinyfiledialogs-master/tinyfiledialogs.h"
#include <stdio.h>
#include <stdlib.h>
#include "Photoshopc.h"

using namespace std;
using namespace cvui;

#define WINDOWS "windows"

void setOption(cv::Mat *frame, string *type, int *currentOption) {
    int width = frame->cols;
    int buttonWidth;
    if (*type == "image") {
        buttonWidth = (int) width / 5;
        if (button(*frame, 0, 0, buttonWidth, 20, "dilatation")) {
            *currentOption = 0;
        }
        if (button(*frame, buttonWidth, 0, buttonWidth, 20, "erosion")) {
            *currentOption = 1;
        }
        if (button(*frame, buttonWidth * 2, 0, buttonWidth, 20, "cannyEdgeDetection")) {
            *currentOption = 2;
        }
        if (button(*frame, buttonWidth * 3, 0, buttonWidth, 20, "luminosity")) {
            *currentOption = 3;
        }
        if (button(*frame, buttonWidth * 4, 0, buttonWidth, 20, "resize")) {
            *currentOption = 4;
        }
    }
}

void showParameters(cv::Mat *frame, int currentOption, Photoshopc* picture, map<string, vector<int>> *values) {
    int height = 160;
    int segment = 90;
    int xWindow = 10;
    int yWindow = 50;
    int type = 1;
    if (currentOption == 2) {
        height += segment * 2;
        type = 3;
    }
    if (currentOption == 4) {
        height += segment;
        type = 2;
    }
    cvui::window(*frame, xWindow, yWindow, 180, height, "Settings");
    switch (currentOption) {
        case 0:
            cvui::text(*frame, xWindow + 5, yWindow + 30, "iteration");
            cvui::trackbar(*frame, xWindow + 5, yWindow + 60, 165, &values->at("dilation").at(0), 0, 100);
            picture->dilatation(values->at("dilation").at(0));
            break;
        case 1:
            cvui::text(*frame, xWindow + 5, yWindow + 30, "iteration");
            cvui::trackbar(*frame, xWindow + 5, yWindow + 60, 165, &values->at("erosion").at(0), 0, 100);
            picture->erosion(values->at("erosion").at(0));
            break;
        case 2:
            cvui::text(*frame, xWindow + 5, yWindow +30, "threshold1");
            cvui::trackbar(*frame, xWindow + 5, yWindow + 60, 165, &values->at("cannyEdgeDetection").at(0), 0, 300);
            cvui::text(*frame, xWindow + 5, yWindow + 120, "threshold2");
            cvui::trackbar(*frame, xWindow + 5, yWindow + 150, 165, &values->at("cannyEdgeDetection").at(1), 0, 300);
            cvui::text(*frame, xWindow + 5, yWindow + 210, "aperture size");
            cvui::trackbar(*frame, xWindow + 5, yWindow + 240, 165, &values->at("cannyEdgeDetection").at(2), 3, 7, 2, "%.0Lf");
            picture->cannyEdgeDetection(values->at("cannyEdgeDetection").at(0), values->at("cannyEdgeDetection").at(1), values->at("cannyEdgeDetection").at(2));
            break;
        case 3:
            cvui::text(*frame, xWindow + 5, yWindow + 30, "luminosity");
            cvui::trackbar(*frame, xWindow + 5, yWindow + 60, 165, &values->at("luminosity").at(0), -200, 200);
            picture->luminosity(values->at("luminosity").at(0));

            break;
        case 4:
            cvui::text(*frame, xWindow + 5, yWindow + 30, "width");
            cvui::trackbar(*frame, xWindow + 5, yWindow + 60, 165, &values->at("resize").at(0), 1, 200);
            cvui::text(*frame, xWindow + 5, yWindow + 120, "heigt");
            cvui::trackbar(*frame, xWindow + 5, yWindow + 150, 165, &values->at("resize").at(1), 1, 200);
            picture->resize(values->at("resize").at(0), values->at("resize").at(1));
            break;
    }
    if (cvui::button(*frame, xWindow + 5, yWindow + type * segment + 25, "Reset")) {
        picture->reset();
    }
    if(type != 3) {
        if (cvui::button(*frame, xWindow + 80, yWindow + type * segment + 25, "Apply")) {
            picture->save();
        }
    }
}

char const * getFile(){
    char const * lTheOpenFileName;
    FILE * lIn;
    char const * lFilterPatterns[2] = { "*.jpg", "*.text" };

    lTheOpenFileName = tinyfd_openFileDialog(
            "let us read the password ",
            "",
            2,
            lFilterPatterns,
            NULL,
            0);

    if (! lTheOpenFileName)
    {
        tinyfd_messageBox(
                "Error",
                "Open file name is NULL",
                "ok",
                "error",
                1);
        return NULL ;
    }

    lIn = fopen(lTheOpenFileName, "r");

    if (!lIn)
    {
        tinyfd_messageBox(
                "Error",
                "Can not open this file in read mode",
                "ok",
                "error",
                1);
        return NULL;
    }
    fclose(lIn);

    return lTheOpenFileName;
}

void addImage(cv::Mat *frame, cv::Mat *image){
    int x = (int) frame->cols/2 - image->cols/2;
    int y = (int) frame->rows/2 - image->rows/2;
//    cout << "type = " << frame->type() <<endl;
//    cout << "type = " << image->type() <<endl;
    if(image->type() == 0){
        cvtColor(*frame, *frame, COLOR_BGR2GRAY);
    }
    image->copyTo(frame->colRange(x, x + image->cols).rowRange(y, y + image->rows));
    if(image->type() == 0) {
        cvtColor(*frame, *frame, COLOR_GRAY2BGR);
    }
}


int main(int argc, char *argv[]) {

    init(WINDOWS);
    cv::namedWindow(WINDOWS);
    cv::Mat frame = cv::Mat(cv::Size(1080, 720), CV_8UC3);
    cv::Mat im1 = cv::imread(getFile());
    string type = "image";
    Photoshopc picture(im1);
    int currentOption = 0;
    map<string, vector<int>> values = {
            {"dilation", {0}},
            {"erosion", {0}},
            {"cannyEdgeDetection", {0, 0, 3}},
            {"luminosity", {0}},
            {"resize", {100, 100}}
    };
    int i = 500;
    Mat currentPic;
    im1.copyTo(currentPic);
    while (true) {

        // clear the frame
        frame = cv::Scalar(49, 52, 49);
        addImage(&frame, picture.getNewImage());
        // render a message in the frame at position (10, 15)
        setOption(&frame, &type, &currentOption);
        showParameters(&frame, currentOption, &picture, &values);
        cvui::imshow(WINDOWS, frame);
        if (cv::waitKey(20) == 27) {
            break;
        }
    }
}
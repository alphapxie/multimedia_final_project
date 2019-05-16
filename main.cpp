#include <iostream>

#define CVUI_IMPLEMENTATION

#include <opencv2/opencv.hpp>
#include "cvui-master/cvui-master/cvui.h"

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

vector<int> showParameters(cv::Mat *frame, int currentOption) {
    int height = 120;
    int segment = 90;
    vector<int> values;
    values.push_back(0);
    values.push_back(0);
    values.push_back(0);
    if (currentOption == 2) {
        height += segment * 2;
    }
    if (currentOption == 4) {
        height += segment;
    }
    cvui::window(*frame, 10, 50, 180, height, "Settings");
    switch (currentOption) {
        case 0:
        case 1:
            cvui::text(*frame, 15, 80, "iteration");
            cvui::trackbar(*frame, 15, 110, 165, &values.at(0), 0, 100);
            break;
        case 2:
            cvui::text(*frame, 15, 80, "threshold1");
            cvui::trackbar(*frame, 15, 110, 165, &values.at(0), 5, 150);
            cvui::text(*frame, 15, 170, "threshold2");
            cvui::trackbar(*frame, 15, 200, 165, &values.at(1), 80, 300);
            cvui::text(*frame, 15, 260, "aperture size");
            cvui::trackbar(*frame, 15, 290, 165, &values.at(2), 1, 10);
            break;
        case 3:
            cvui::text(*frame, 15, 80, "luminosity");
            cvui::trackbar(*frame, 15, 110, 165, &values.at(0), -200, 200);
            break;
        case 4:
            cvui::text(*frame, 15, 80, "width");
            cvui::trackbar(*frame, 15, 110, 165, &values.at(0), 0, 100);
            cvui::text(*frame, 15, 170, "heigt");
            cvui::trackbar(*frame, 15, 200, 165, &values.at(1), 0, 100);
            break;
    }
    return values;
}



int main(int argc, char *argv[]) {
    init(WINDOWS);
    cv::Mat frame = cv::Mat(cv::Size(1080, 720), CV_8UC3);
    cv::Mat im1 = cv::imread("../1.jpg");
    string type = "image";
    vector<int> values;
    int currentOption;
    int i = 1;
    const char *format = "%d";
    while (true) {
        // clear the frame
        frame = cv::Scalar(49, 52, 49);

        // render a message in the frame at position (10, 15)
        setOption(&frame, &type, &currentOption);
        values = showParameters(&frame, currentOption);
        cvui::imshow(WINDOWS, frame);
        if (cv::waitKey(20) == 27) {
            break;
        }
    }
    return 0;
}
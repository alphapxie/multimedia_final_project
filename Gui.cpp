//
// Created by victo on 05/06/2019.
//
#include "Gui.h"
#include <chrono>
using namespace std::chrono;

void Gui::setOption() {
    int width = frame.cols;
    int buttonWidth;
    buttonWidth = (int) width / 5;
    if (button(frame, 0, 0, buttonWidth, 20, "dilatation")) {
        currentOption = 0;
    }
    if (button(frame, buttonWidth, 0, buttonWidth, 20, "erosion")) {
        currentOption = 1;
    }
    if (button(frame, buttonWidth * 2, 0, buttonWidth, 20, "cannyEdgeDetection")) {
        currentOption = 2;
    }
    if (button(frame, buttonWidth * 3, 0, buttonWidth, 20, "luminosity")) {
        currentOption = 3;
    }
    if (button(frame, buttonWidth * 4, 0, buttonWidth, 20, "resize")) {
        currentOption = 4;
    }
}

void Gui::showParameters(bool hasOption) {
    int height = 190;
    int segment = 90;
    int xWindow = 10;
    int yWindow = 50;
    int type = 1;
//    if (hasOption) {
//        height += 50;
//    }
    if (currentOption == 2) {
        height += segment * 2;
        type = 3;
    }
    if (currentOption == 4) {
        height += segment;
        type = 2;
    }

    cvui::window(frame, xWindow, yWindow, 180, height, "Settings");


    switch (currentOption) {
        case 0:
            cvui::text(frame, xWindow + 5, yWindow + 30, "iteration");
            cvui::trackbar(frame, xWindow + 5, yWindow + 60, 165, &values.at("dilation").at(0), 0, 100);
            break;
        case 1:
            cvui::text(frame, xWindow + 5, yWindow + 30, "iteration");
            cvui::trackbar(frame, xWindow + 5, yWindow + 60, 165, &values.at("erosion").at(0), 0, 100);
            break;
        case 2:
            cvui::text(frame, xWindow + 5, yWindow + 30, "threshold1");
            cvui::trackbar(frame, xWindow + 5, yWindow + 60, 165, &values.at("cannyEdgeDetection").at(0), 0, 1000);
            cvui::text(frame, xWindow + 5, yWindow + 120, "threshold2");
            cvui::trackbar(frame, xWindow + 5, yWindow + 150, 165, &values.at("cannyEdgeDetection").at(1), 0, 1000);
            cvui::text(frame, xWindow + 5, yWindow + 210, "aperture size");
            cvui::trackbar(frame, xWindow + 5, yWindow + 240, 165, &values.at("cannyEdgeDetection").at(2), 3, 7, 2,
                           "%.0Lf");
            // avoid 4 and 6 as values for aperture size (forbidden values)
            values.at("cannyEdgeDetection").at(2) = values.at("cannyEdgeDetection").at(2) + (1 - values.at("cannyEdgeDetection").at(2)%2);
            break;
        case 3:
            cvui::text(frame, xWindow + 5, yWindow + 30, "luminosity");
            cvui::trackbar(frame, xWindow + 5, yWindow + 60, 165, &values.at("luminosity").at(0), -200, 200);

            break;
        case 4:
            cvui::text(frame, xWindow + 5, yWindow + 30, "width");
            cvui::trackbar(frame, xWindow + 5, yWindow + 60, 165, &values.at("resize").at(0), 1, 200);
            cvui::text(frame, xWindow + 5, yWindow + 120, "height");
            cvui::trackbar(frame, xWindow + 5, yWindow + 150, 165, &values.at("resize").at(1), 1, 200);
            break;
    }

    cvui::checkbox(frame, xWindow + 5, yWindow + type * segment + 25, "Facial recognition", &facialRecognition);

    if (cvui::button(frame, xWindow + 5, yWindow + type * segment + 55, "Reset")) {
        resetImage();
    }

}

void Gui::updateImage() {
    photoshopObject.getImage()->copyTo(temp);

    photoshopObject.dilatation(values.at("dilation").at(0));
    photoshopObject.save();

    photoshopObject.erosion(values.at("erosion").at(0));
    photoshopObject.save();

    photoshopObject.luminosity(values.at("luminosity").at(0));
    photoshopObject.save();

    photoshopObject.resize(values.at("resize").at(0), values.at("resize").at(1));
    photoshopObject.save();

    if(currentOption == 2) {
        photoshopObject.cannyEdgeDetection(values.at("cannyEdgeDetection").at(0),
                                           values.at("cannyEdgeDetection").at(1),
                                           values.at("cannyEdgeDetection").at(2));
        photoshopObject.save();
    }

    photoshopObject.setImage(temp);
}

void Gui::resetImage(){
    if(!isVideo) {
        photoshopObject.reset();
    }
    values = {
            {"dilation",           {0}},
            {"erosion",            {0}},
            {"cannyEdgeDetection", {0, 0, 3}},
            {"luminosity",         {0}},
            {"resize",             {100, 100}}
    };
}

void Gui::addImage(cv::Mat *image) {
    int x = (int) frame.cols / 2 - image->cols / 2;
    int y = (int) frame.rows / 2 - image->rows / 2;
    if (image->type() <= 7) {
        cvtColor(frame, frame, COLOR_BGR2GRAY);
    }
    image->copyTo(frame.colRange(x, x + image->cols).rowRange(y, y + image->rows));

    if (image->type() <= 7) {
        cvtColor(frame, frame, COLOR_GRAY2BGR);
    }
}

int Gui::showInterface(int type) {
    VideoCapture video;
    Mat newFrame;
    FaceDetection faceDetector = FaceDetection();
    switch (type) {
        case 0:
            video = VideoCapture(0);
            break;
        case 1:
            video = VideoCapture(FileReader::getFile(videoType));
            break;
        case 2:
            photoshopObject = Photoshopc(FileReader::getFile(imageType));
            break;
        case 3:
            photoshopObject = Photoshopc(FileReader::getFiles(imageType));
            break;
        default:
            return 0;
    }
    newFrame = *photoshopObject.getImage();
    frame = cv::Mat(cv::Size(1080, 720), CV_8UC3);
    isVideo = !(type == 2 || type == 3);
    while (true) {
        frame = cv::Scalar(49, 52, 49);
        if (isVideo) {
            video >> newFrame;
            if (newFrame.empty()) {
                video.set(CAP_PROP_POS_FRAMES, 0);
                video >> newFrame;
            }
        }
        photoshopObject.setImage(newFrame);
        addImage(photoshopObject.getNewImage());
        setOption();
        updateImage();
        showParameters(!facialRecognition && !isVideo);

        if (facialRecognition) {
            faceDetector.detectAndDisplay(photoshopObject.getNewImage());
        }
        cvui::imshow(WINDOWS, frame);
        if (cv::waitKey(20) == 27) {
            break;
        }
    }
    return 1;
}

int Gui::startMenu() {
    resetImage();
    if (button(frame, 0, 0, 200, 200, "Photo")) {
        return showInterface(2);
    }
    if (button(frame, 200, 0, 200, 200, "Video")) {
        return showInterface(1);
    }
    if (button(frame, 0, 200, 200, 200, "Panorama")) {
        return showInterface(3);
    }
    if (button(frame, 200, 200, 200, 200, "Camera")) {
        return showInterface(0);
    }
    return 1;
}

void Gui::startGui() {
    init(WINDOWS);
    cv::namedWindow(WINDOWS);
    while (true) {
        frame = cv::Mat(cv::Size(400, 400), CV_8UC3);
        frame = cv::Scalar(49, 52, 49);
        startMenu();
        cv::imshow(WINDOWS, frame);
        if (cv::waitKey(20) == 27) {
            break;
        }
    }
}
//
// Created by Grégoire on 09/05/2019.
//

#ifndef MULTIMEDIA_FINAL_PROJECT_FACE_DETECTION_H
#define MULTIMEDIA_FINAL_PROJECT_FACE_DETECTION_H
#include <opencv2/opencv.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class FaceDetection {
    String face_cascade_name = "../haarcascade_frontalface_alt2.xml";
    String eyes_cascade_name = "../haarcascade_eye_tree_eyeglasses.xml";
    CascadeClassifier face_cascade;
    CascadeClassifier eyes_cascade;
    string window_name = "Capture - Face detection";
public:
    FaceDetection();
    void detectAndDisplay( Mat* frame );

};


#endif //MULTIMEDIA_FINAL_PROJECT_FACE_DETECTION_H

//
// Created by Grégoire on 09/05/2019.
//

#ifndef MULTIMEDIA_FINAL_PROJECT_FACE_DETECTION_H
#define MULTIMEDIA_FINAL_PROJECT_FACE_DETECTION_H
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class FaceDetection {
public:
    FaceDetection();
    void detectAndDisplay( Mat frame );

};


#endif //MULTIMEDIA_FINAL_PROJECT_FACE_DETECTION_H

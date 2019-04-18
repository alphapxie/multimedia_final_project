//
// Created by victo on 18/04/2019.
//

#include "Photoshopc.h"

Photoshopc::Photoshopc(String* path) {
    this->image = imread(*path);
}

Photoshopc::Photoshopc(int x, int y) {
    this->image = Mat::zeros(cv::Size(x, y), CV_64FC1);
}
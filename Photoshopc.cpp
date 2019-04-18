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

Mat Photoshopc::luminosity(int luminosity) {
    Mat newImage;
    image.convertTo(newImage, -1, 1, luminosity);
    return newImage;
}

Mat Photoshopc::panorama(vector<Mat>* images) {
    Stitcher::Mode mode = Stitcher::PANORAMA;
    Mat pano;
    Ptr<Stitcher> stitcher = Stitcher::create(mode);
    Stitcher::Status status = stitcher->stitch(*images, pano);
    if (status != Stitcher::OK)
    {
        cout << "Can't stitch images\n";
        return images->at(0);
    }
    return pano;
}
//
// Created by victo on 18/04/2019.
//

#include "Photoshopc.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;


Photoshopc::Photoshopc(String path) {
    this->image = imread(path);
    this->newImage = imread(path);
    this->src = imread(path);
}

Photoshopc::Photoshopc(int x, int y) {
    this->image = Mat::zeros(cv::Size(x, y), CV_64FC1);
    this->newImage = Mat::zeros(cv::Size(x, y), CV_64FC1);
    this->src = Mat::zeros(cv::Size(x, y), CV_64FC1);
}

Photoshopc::Photoshopc(Mat img) {
    img.copyTo(image);
    img.copyTo(newImage);
    img.copyTo(src);
}

Photoshopc::Photoshopc(vector<string> fileList) {
    vector<Mat> matList;
    for (string file : fileList) {
        matList.push_back(cv::imread(file));
    }
    Mat fullPicture = panorama(&matList);
    fullPicture.copyTo(src);
    src.copyTo(image);
    src.copyTo(newImage);
}
void Photoshopc::dilatation(int iteration){
    dilate(image, newImage, Mat(), Point (-1, -1), iteration);
}

void Photoshopc::erosion(int iteration){
    erode(image, newImage, Mat(), Point (-1, -1), iteration);
}

void Photoshopc::cannyEdgeDetection(double thresh1=100, double thresh2=200, int apertureSize=3){
    Mat dest;
    if(apertureSize%2 == 0 || apertureSize < 3 || apertureSize > 7){
        cout << "Aperture size should be odd between 3 and 7" << endl;
        return;
    }
    Canny(this->image, newImage, thresh1, thresh2, apertureSize, false);
}

void Photoshopc::luminosity(int luminosity) {
    image.convertTo(newImage, -1, 1, luminosity);
}

void Photoshopc::resize(double a, double b)
{
	Mat dst;
	int width = MIN(MAX(round(a*image.cols/100), 1), 1080);
	int height = MIN(MAX(round(b*image.rows/100), 1), 720);
	cv::resize(image, newImage, Size(width, height),INTER_LINEAR);
}



Mat Photoshopc::panorama(vector<Mat>* images) {
    Mat fullImage;
    Stitcher::Mode mode = Stitcher::PANORAMA;
    Ptr<Stitcher> stitcher = Stitcher::create(mode);
    Stitcher::Status status = stitcher->stitch(*images, fullImage);
    if (status != Stitcher::OK)
    {
        cout << "Can't stitch images\n";
        return images->at(0);
    }
    return fullImage;
}

void Photoshopc::setImage(Mat picture) {
    picture.copyTo(image);
}

Mat* Photoshopc::getImage() {
    return &this->image;
}
Mat* Photoshopc::getNewImage() {
    return &this->newImage;
}

void Photoshopc::save() {
    newImage.copyTo(image);
}

void Photoshopc::reset() {
    src.copyTo(image);
    src.copyTo(newImage);
}
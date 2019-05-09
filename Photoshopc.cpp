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




Mat Photoshopc::dilatation(int iteration){
    Mat dest;
    dilate(this->image, dest, 0, Point (-1,1), iteration, BORDER_REFLECT101, morphologyDefaultBorderValue());
}

Mat Photoshopc::erosion(int iteration){
    Mat dest;
    erode(this->image, dest, 0, Point (-1,1), iteration, BORDER_REFLECT101, morphologyDefaultBorderValue());
}

Mat Photoshopc::cannyEdgeDetection(double thresh1=100, double thresh2=200, int apertureSize=3){
    Mat dest;
    Canny(this->image, dest, thresh1, thresh2, apertureSize, false);
}
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

Mat Photoshopc::resize(double a, double b)
{
	Mat dst;
	cv::resize(image, dst, Size((int) round(a*image.cols),(int) round(b*image.rows)),INTER_LINEAR);
	return dst;
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
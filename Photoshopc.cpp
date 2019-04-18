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
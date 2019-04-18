//
// Created by Grégoire on 18/04/2019.
//

#include "Video.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat Video::brightness(int brightnessLevel){

    Mat frame;
    Mat frame2;
    if(!video.isOpened()){
        cout << "cannot find video" << endl;
    }
    while (true) {
        // read a new frame from video
        video >> frame;
        //Breaking the while loop at the end of the video
        if(frame.empty()){
            break;
        }

        //increase the brightness by 50
        for(int i=0; i<frame.rows; i++){
            for(int j=0; j<frame.cols; j++){
                for (int c=0; c<3; c++){
                    frame2.at<Vec3b>(i,j)[c] = saturate_cast<uchar>(frame.at<Vec3b>(i,j)[c] + brightnessLevel);
                }
            }
        }

        //Show above frames inside the created windows.
        imshow("video", frame);
        imshow("video", frame2);

        if (waitKey(10) == 27)
        {
            cout << "Esc key is pressed by user. Stoppig the video" << endl;
            break;
        }
    }
    destroyAllWindows();
}

Mat Video::Gaussian(int x, int y){

    Mat frame;
    Mat frame2;

if (!video.isOpened()) {
    cout << "cannot find video" << endl;
}


while (1) {
video >> frame; // read a new frame from video

    if(frame.empty()){
        break;
    }
//Blur the frame with 5x5 Gaussian kernel

GaussianBlur(frame, frame2, Size(x,y), 4, 10);

//show the frames in the created windows
imshow("video", frame2);

if(waitKey(10)==27){
break;
}
}

destroyAllWindows();
}


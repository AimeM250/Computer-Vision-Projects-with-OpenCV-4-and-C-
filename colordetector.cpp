//Header files for OpenCV
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
using namespace cv;
using namespace std;

///// Object detection based on colors//////



int main(){


    Mat imgHSV, mask;
    int hmin= 0,smin = 110, vmin= 153;
    int hmax = 19,smax= 240, vmax= 255;

    string path = "Resources/shapes.png";
    Mat img = imread(path); ///Mat (datatype introduced by OPEnCV for handling images )
    
    cvtColor(img, imgHSV, COLOR_BGR2HSV);
    namedWindow("Trackbars",(640, 200));
    
    /*
    Trackbars help the user adjust the value of an integer variable within
    a given range of numbers

    */
    createTrackbar("Hue Min", "Trackbars", &hmin, 180);
    createTrackbar("Hue Max", "Trackbars", &hmax, 180);
    createTrackbar("Sat Min", "Trackbars", &smin, 255);
    createTrackbar("Sat Max", "Trackbars", &smax, 255);
    createTrackbar("Val Min", "Trackbars", &vmin, 255);
    createTrackbar("Val Max", "Trackbars", &vmax, 255);


    while(true){




        

    Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);

        inRange(imgHSV, lower, upper, mask);
        //HSV Stands for Hue Saturation Value and it is used to separate image luminance from color information.

        //inRange(imgHSV, Scalar(0, 110, 153), Scalar(19, 240, 255), mask); // This can be also used


       // imshow("Image", img);
        //imshow("Image HSV", imgHSV);
        imshow("Image Mask", mask);


        waitKey(1); // Wait for a keystroke in the window

    }
    return 0;
    
}
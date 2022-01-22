//Header files for OpenCV
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
using namespace cv;
using namespace std;

///// Object detection based on colors//////

/*
    VideoCapture cap(0); // Video capture object( cap ) for the camera
    Mat img;
    while(true){  // Infinite while loop 
 
        cap.read(img);  // read method for reading the frames within the video using the object cap
        imshow("Image",img); // Showing or displaying the frames in the video

        if (waitKey(50) == 'k') break; // Breaking the loop in case the user clicks on 'K'

    }

*/
int main(){

    Mat imgHSV, mask,img;
    VideoCapture cap(0);

    int hmin= 0,smin = 0, vmin= 0;
    int hmax = 179,smax= 240, vmax= 255;

    //string path = "Resources/shapes.png";
   // Mat img = imread(path); ///Mat (datatype introduced by OPEnCV for handling images )

        //VideoCapture cap(0); // Video capture object( cap ) for the camera
    //Mat img;

    
    namedWindow("Trackbars",(640, 200));
    /*
    Trackbars help the user adjust the value of an integer variable within
    a given range of numbers

    */
    createTrackbar("Hue Min", "Trackbars", &hmin, 179);
    createTrackbar("Hue Max", "Trackbars", &hmax, 179);
    createTrackbar("Sat Min", "Trackbars", &smin, 255);
    createTrackbar("Sat Max", "Trackbars", &smax, 255);
    createTrackbar("Val Min", "Trackbars", &vmin, 255);
    createTrackbar("Val Max", "Trackbars", &vmax, 255);

    // while(true){  // Infinite while loop 

    


    // imshow("Image",imgHSV); // Showing or displaying the frames in the video

    // if (waitKey(50) == 'k') break; // Breaking the loop in case the user clicks on 'K'

    // }

    while(true){  

        
        cap.read(img);  // read method for reading the frames within the video using the object cap

        cvtColor(img, imgHSV, COLOR_BGR2HSV);


        Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);

        inRange(imgHSV, lower, upper, mask); // InRange Function is used in Thresholding, 
        //for converting an image from rgb color space to hsv color space.
        //HSV Stands for Hue Saturation Value and it is used to separate image luminance from color information.

        //inRange(imgHSV, Scalar(0, 110, 153), Scalar(19, 240, 255), mask); // This can be also used


       // imshow("Image", img);
        //imshow("Image HSV", imgHSV);

        imshow("Image", img);
        imshow("Image Mask", mask);


        waitKey(1); // Wait for a keystroke in the window

    }
    return 0;
    
}
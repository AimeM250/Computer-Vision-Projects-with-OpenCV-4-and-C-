//Header files for OpenCV
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
using namespace cv;
using namespace std;

/*
The following are the steps to complete the project:


...Firstly, compute the image's preprocessing phase, which includes converting the image to grayscale and applying blur, and then use the Canny Edge detector to discover all of its edges.


....Secondly, once the edges have been discovered, they will assist us in determining the location of the coordinates corners of the paper (Getting contours) )


.....Finally, warp the paper and obtain a topview such that it appears scanned. 
*/

Mat imgOrig,imgGray, imgBlur, imgcanny, imgDil, imgErode;
vector<Point> initialPoints;

Mat preProcessing(Mat img)
{

    cvtColor(img, imgGray, COLOR_BGR2GRAY); // Changing image to Gray
    GaussianBlur(img, imgBlur, Size(3,3), 3,0); // Blurring image
    Canny(imgBlur, imgcanny,25,75); // Edge detection

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3)); // Creating a kernel that will be used for dilation
    dilate(imgcanny, imgDil, kernel);
    erode(imgDil, imgErode, kernel);

    return imgDil;



}

vector<Point> getContours (Mat imgDil){

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    //drawContours(img, contours,-1, Scalar(255,0,255),5); // THe minus one means that we want to drae all the contours that will be detected.

    // Removing noise
    
    vector<vector<Point>> conPoly(contours.size()); // Declaration of an array
    vector<Rect> boundRect(contours.size()); // Variable( Vector) that we are introducing

    vector<Point> biggest;
    int maxArea = 0;

    for (int i = 0; i< contours.size(); i++){

         //Mat img;

         int area = contourArea(contours[i]);
        // cout<<"The area of the given contour is: "<<area <<endl;

         
         if (area > 1000){

             float peri = arcLength(contours[i],true); // Computing the perimeter of each shape & then if passed true means that the shape is a closed contour.

             approxPolyDP(contours[i], conPoly[i], 0.02*peri, true); // The following function performs an approximation of a shape of a contour

             
            if ( area > maxArea && conPoly[i].size()==4)
            {

                biggest = { conPoly[i][0], conPoly[i][1], conPoly[i][2], conPoly[i][3] };
                maxArea = area;
            }


             drawContours(imgOrig, conPoly, i, Scalar(255,0,255),2);

             //rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5); // Function for inding the bounding rectangle around the detected image.


             //cout<< conPoly[i].size()<<endl;

                   

              

         }

    }

    return biggest;

}

void drawPoints (vector<Point> points, Scalar color)
{

    for (int i = 0; i< points.size(); i++)
    {
        circle(imgOrig, points[i], 30, color, FILLED);
        putText(imgOrig, to_string(i), points[i], FONT_HERSHEY_PLAIN, 5, color, 5);
    }


}

int main(){

    string path = "Resources/paper.jpg";
    imgOrig = imread(path); ///Mat (datatype introduced by OPEnCV for handling images)

    resize(imgOrig, imgOrig, Size(), 0.5, 0.5); // Resizing half the image

    // Preprocessing

    Mat imgThre = preProcessing(imgOrig);

    // Getcontours

    initialPoints = getContours(imgThre);

    drawPoints(initialPoints, Scalar(0,0,255));



    

    imshow("Image", imgOrig);
    imshow("Image Threshoded", imgThre);

    waitKey(0);

    return 0;
    
}
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>


#include <iostream>
#include <string>
using namespace cv;
using namespace std;

/// Simple project for Painting virtually using OPENCV4////

/*Steps to be followed:

We will first detect the colors using HSV space,
once we have the color image, we will pass it to 
the contour method to find where their contours are,
once found, we will take their x and y positions and 
then draw a circle at that location. 

*/
    Mat img;
    vector<vector<int>> newPoints; // This means that we have one vector that contains more vectors within it as shown below having the value of x, y , and the value of the color ( either 1 or two ) {{x, y,0},{x,y,1}}}

///
    int hmin= 0,smin = 110, vmin= 153;
    int hmax = 19,smax= 240, vmax= 255;

vector<vector<int>> myColors{ {152,179,149,240,070,255}, // Red 
                                 {020,28,108,240,000,255} };// Yellow

vector<Scalar>myColorValues { (255,0,255),(255,0,0) // In case Purple has been detected, the Purple color will be automatically displayed on screen ( BGR (Purple = BLue+ Green))
                                }; // Yellow Color will be displayed.



Point getContours (Mat imgDil){

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    //drawContours(img, contours,-1, Scalar(255,0,255),5); // THe minus one means that we want to drae all the contours that will be detected.

    // Removing noise
    
    vector<vector<Point>> conPoly(contours.size()); // Declaration of an array
    vector<Rect> boundRect(contours.size()); // Variable( Vector) that we are introducing

    Point myPoint(0,0);

    for (int i = 0; i< contours.size(); i++){

         //Mat img;

         int area = contourArea(contours[i]);
        // cout<<"The area of the given contour is: "<<area <<endl;

         
         if (area > 1000){

             float peri = arcLength(contours[i],true); // Computing the perimeter of each shape & then if passed true means that the shape is a closed contour.

             approxPolyDP(contours[i], conPoly[i], 0.02*peri, true); // The following function performs an approximation of a shape of a contour

             //cout<< conPoly[i].size()<<endl;
             boundRect[i] = boundingRect(conPoly[i]);

             myPoint.x = boundRect[i].x + boundRect[i].width/2; // Divided by 2 because we want to draw it by the center not at the edge.
             myPoint.y = boundRect[i].y;




             drawContours(img, conPoly, i, Scalar(255,0,255),2);

             //rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5); // Function for inding the bounding rectangle around the detected image.


             //cout<< conPoly[i].size()<<endl;

                   

              

         }

    }

    return myPoint;

}


vector<vector<int>> findColor(Mat img){ // Function for detecting a color of a certain Object

    Mat imgHSV;
    cvtColor(img, imgHSV, COLOR_BGR2HSV);

    for (int i = 0; i< myColors.size(); i++){


        Scalar lower(myColors[i][0], myColors[i][2], myColors[i][4]);
        Scalar upper(myColors[i][1], myColors[i][3], myColors[i][5]);
        Mat mask;
        inRange(imgHSV, lower, upper, mask);
        imshow(to_string(i), mask);

        Point myPoint = getContours(mask);

        if(myPoint.x !=0 && myPoint.y != 0) {

            newPoints.push_back({myPoint.x, myPoint.y,i});


        }

        
    }

    return newPoints;
}

void drawOnCanvas(vector<vector<int>> newPoints,vector<Scalar> myColorValues){

    for (int i = 0; i < newPoints.size(); i++)
    {
        circle(img, (Point(newPoints[i][0],newPoints[i][1])), 10, myColorValues[newPoints[i][2]], FILLED);
    }
}

int main(){

    VideoCapture cap(0); // Video capture object( cap ) for the camera
    while(true){  // Infinite loop 
 
        cap.read(img);  // read method for reading the frames within the video using the object cap
        newPoints = findColor(img);
       //findColor(img);
        drawOnCanvas(newPoints, myColorValues);
        imshow("Image",img); // Showing or displaying the frames in the video
        waitKey(25);
       // if (waitKey(50) == 'k') break; // Breaking the loop in case the user clicks on 'K'

    }
}
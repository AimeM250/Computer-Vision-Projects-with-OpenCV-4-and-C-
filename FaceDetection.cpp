//Header files for OpenCV
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/objdetect.hpp>  // Library for Face detection
#include<iostream>
using namespace cv;
using namespace std;

// A simple program for face detection

int main(){

    string path = "Resources/test.png";
    Mat img = imread(path); ///Mat (datatype introduced by OPEnCV for handling images 
    CascadeClassifier faceCascade; // A pre-trained model that can be read from CV
    faceCascade.load("Resources/haarcascade_frontalface_default.xml"); // Loading the object detection algorthm for identifying faces in images or real time video called Haar Cascade

    if(faceCascade.empty()){cout<<"XML file is not loaded"<<endl;} // Checking whether it is working properly or not.

    vector<Rect> faces;
    faceCascade.detectMultiScale(img,faces, 1.1, 10); // A method in cascade classifier for returning detected faces or eyes

    for (int i = 0; i< faces.size(); i++){
        rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255,0,255),3); // Boundary Rectangle to be returned on the detected faces
    }

    imshow("Image", img);
    


    waitKey(0); // Wait for a keystroke in the window
  
    return 0;
    
}
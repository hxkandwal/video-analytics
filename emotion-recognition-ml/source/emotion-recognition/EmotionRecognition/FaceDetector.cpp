//
//  FaceDetector.cpp
//  EmotionRecognition
//
//  Created by Himanshu Kandwal on 5/7/16.
//  Copyright © 2016 Himanshu Kandwal. All rights reserved.
//
#include "opencv/cv.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <stdio.h>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include <iterator>
#include "stasm_lib.h"
#include "svmClassifier.h"
#include "ASMCalculator.hpp"

using namespace cv;
using namespace std;

ASMCalculator asmCalculator;
SvmClassifier svmclassifier;

// Create a new Haar classifier
static CvHaarClassifierCascade* cascade = 0;

// Function prototype for detecting and drawing an object from an image
void detect_and_draw( IplImage* image , std::string imageType);

// Create a string that contains the cascade name
const char* cascade_name = "/Users/Heman/Documents/workstation/Applications/opencv/opencv-2.4.11/data/haarcascades/otherhaarcascade_frontalface_alt.xml";

const char* path = "/Users/Heman/Documents/workstation/Developement_Studio/Xcode_Laboratory/EmotionRecognition/EmotionRecognition/EmotionRecognition/data/out/temp/temp_image.jpeg";

const char* initalImagePath = "/Users/Heman/Documents/workstation/Developement_Studio/Xcode_Laboratory/EmotionRecognition/EmotionRecognition/EmotionRecognition/data/out/temp/inital_image.jpeg";

int initCount = 0;

bool detect(std::string filename) {
    
    std::string imageType;
    
    bool result = true;
    
    if (filename.empty() || filename.length() == 0 || filename.find("MOV") == std::string::npos)
        imageType = "Not Mov";
    else
        imageType = "MOV";
    
    // Load the [[HaarClassifierCascade]]
    cascade = (CvHaarClassifierCascade*) cvLoad( cascade_name );
    
    // Check whether the cascade has loaded successfully. Else report and error and quit
    if( !cascade )
    {
        fprintf( stderr, "ERROR: Could not load classifier cascade\n" );
        return -1;
    }
    
    // Create a new named window with title: result
    cvNamedWindow( "result", 1 );

    VideoCapture capture;
    
    // Load the image from that filename
    if (filename.empty() && filename.length() == 0) {
        capture.open( -1 );
    } else {
        capture.open( filename );
    }

    Mat frame;
    
    //-- 2. Read the video stream
    if( capture.isOpened() )
    {
        for(;;) {
            long loop = 0;
              
            if (loop++ % 30 == 0) {
                initCount ++;
                    
                capture >> frame;
                    
                // draw inital image after 3 secs.
                if (initCount == 6) {
                        
                    // delete the old file.
                    std::remove(initalImagePath);
                        
                    imwrite( initalImagePath, frame );
                }
                    
                //-- 3. Apply the classifier to the frame
                if( !frame.empty() ) {
                    IplImage* image = cvCreateImage(cvSize(frame.cols, frame.rows), 8, 3);
                    IplImage ipltemp = frame;
                    cvCopy(&ipltemp, image);
                    
                    detect_and_draw(image, imageType);
                }
                else {
                    printf(" --(!) No captured frame -- Break!"); break;
                }
                
                int c = cvWaitKey(1);
                
                if (char(c) == 27)
                    break;
            }
        }
    }
    
    // Destroy the window previously created with filename: "result"
    cvDestroyWindow("result");
    
    return result;
}


// Function to detect and draw any faces that is present in an image
void detect_and_draw( IplImage* img , std::string imageType)
{
    int scale = 1;
    
    // Create a new image based on the input image
    // IplImage* temp = cvCreateImage ( cvSize(img -> width/scale,img->height/scale), 8, 3 );
    
    // Create two points to represent the face locations
    CvPoint pt1, pt2;
    
    int i;
    
    CvMemStorage* storage = cvCreateMemStorage(0);
    
    // Clear the memory storage which was used before
    cvClearMemStorage( storage );
    
    // Find whether the cascade is loaded, to find the faces. If yes, then:
    if( cascade )
    {
        
        // There can be more than one face in an image. So create a growable sequence of faces.
        // Detect the objects and store them in the sequence
        CvSeq* faces = cvHaarDetectObjects( img, cascade, storage, 1.1, 2, CV_HAAR_DO_CANNY_PRUNING, cvSize(40, 40) );
        
        // Loop the number of faces found.
        for( i = 0; i < (faces ? faces->total : 0); i++ )
        {
            // Create a new rectangle for drawing the face
            CvRect* r = (CvRect*) cvGetSeqElem( faces, i );
            
            // Find the dimensions of the face,and scale it if necessary
            pt1.x = r->x*scale;
            pt2.x = (r->x+r->width)*scale;
            pt1.y = r->y*scale;
            pt2.y = (r->y+r->height)*scale;
            
            // Draw the rectangle in the input image
            cvRectangle( img, pt1, pt2, CV_RGB(255, 0, 0), 3, 4, 0 );
        }
    }
    
    
    Mat imageIplMat = img;
    imwrite( path, imageIplMat );
    
    asmCalculator.findASMData(svmclassifier, imageType);
}

int main()
{
    svmclassifier.training();
    
     detect ("");
    
    // detect ("/Users/Heman/Downloads/RecognizeEmotion.avi");
    
    // detect ("/Users/Heman/Documents/workstation/College/Classwork/Projects/VA/EmotionRecognitionVideo1.avi");
    
    // detect ("/Users/Heman/Documents/workstation/College/Classwork/Projects/VA/EmotionRecognitionVideo2.MOV");
    
    return 0;
}
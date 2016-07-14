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
#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include <iterator>
#include "stasm_lib.h"
#include "svmClassifier.h"

using namespace cv;
using namespace std;

SvmClassifier svmclassifier;

// Create a new Haar classifier
static CvHaarClassifierCascade* cascade = 0;

// Function prototype for detecting and drawing an object from an image
void detect_and_draw( IplImage* image );

// Create a string that contains the cascade name
const char* cascade_name = "/Users/Heman/Documents/workstation/Applications/opencv/opencv-2.4.11/data/haarcascades/otherhaarcascade_frontalface_alt.xml";

const char* path = "/Users/Heman/Documents/workstation/Developement_Studio/Xcode_Laboratory/EmotionRecognition/EmotionRecognition/EmotionRecognition/data/out/temp/temp_image.jpeg";

int initCount = 0;

float xInitial = 0;
float yInitial = 0;


float initialFeatureVetor[154];
float currentFeatureVetor[154];

void asmfind () {
    bool storeInitial = false;
    
    float xInterim = 0;
    float yInterim = 0;
    
    int changed = 0;
    
    cv::Mat_<unsigned char> img(cv::imread(path, CV_LOAD_IMAGE_GRAYSCALE));
    
    if (initCount == 6 || (xInitial == 0 && yInitial == 0))
        storeInitial = true;
    
    if (!img.data)
    {
        printf("Cannot load %s\n", path);
        exit(1);
    }
    
    int foundface;
    float landmarks[2 * stasm_NLANDMARKS]; // x,y coords (note the 2)
    
    if (!stasm_search_single(&foundface, landmarks,
                             (const char*) img.data, img.cols, img.rows, path, "/Users/Heman/Documents/workstation/Applications/opencv/opencv-2.4.11/data/testing/"))
    {
        printf("Error in stasm_search_single: %s\n", stasm_lasterr());
        exit(1);
    }
    
    if (!foundface) {
        printf("No face found in %s\n", path);
    }
    else
    {
        int index = 0;
        
        float flowPreviousXPoint = 0;
        float flowPreviousYPoint = 0;
        
        // draw the landmarks on the image as white dots (image is monochrome)
        stasm_force_points_into_image(landmarks, img.cols, img.rows);
        for (int i = 0; i < stasm_NLANDMARKS; i++) {
            img(cvRound(landmarks[i*2+1]), cvRound(landmarks[i*2])) = 255;
            
            if (storeInitial == true) {
                initialFeatureVetor [index ++] = cvRound(landmarks[i*2+1]);
                initialFeatureVetor [index ++] = cvRound(landmarks[i*2]);
                
                xInitial += cvRound(landmarks[i*2+1]);
                yInitial += cvRound(landmarks[i*2]);
                
                if (flowPreviousXPoint == 0 && flowPreviousYPoint ==0) {
                    flowPreviousXPoint = cvRound(landmarks[i*2+1]);
                    flowPreviousYPoint = cvRound(landmarks[i*2]);
                }
            }
            else {
        
                int delta1 = initialFeatureVetor [index] - cvRound(landmarks[i*2+1]);
                currentFeatureVetor[index ++] = delta1;
           
                
                delta1 = initialFeatureVetor [index] - cvRound(landmarks[i*2]);
                currentFeatureVetor[index ++] = delta1;
                
                
                
                xInterim += cvRound(landmarks[i*2+1]);
                yInterim += cvRound(landmarks[i*2]);
                
                if (flowPreviousXPoint == 0 && flowPreviousYPoint ==0) {
                    flowPreviousXPoint = cvRound(landmarks[i*2+1]);
                    flowPreviousYPoint = cvRound(landmarks[i*2]);
                } else {
                    line(img, Point(flowPreviousYPoint, flowPreviousXPoint), Point(cvRound(landmarks[i*2]), cvRound(landmarks[i*2+1])), Scalar(0, 0, 255));
                    
                    flowPreviousXPoint = cvRound(landmarks[i*2+1]);
                    flowPreviousYPoint = cvRound(landmarks[i*2]);
                }
            }
        }
        
        cv::Mat queryFeature = cv::Mat(1, 154, CV_32F, currentFeatureVetor);
        
        float outputHappy = svmclassifier.predictionHappy(queryFeature);
        float outputSurprised = svmclassifier.predictionSurprised(queryFeature);
        float outputDisgust = svmclassifier.predictionDisgust(queryFeature);
        float outputAnger = svmclassifier.predictionAnger(queryFeature);
        
        
        ostringstream predictionInformation;
        predictionInformation <<  " Prediction : " ;
        if (outputHappy != 0)
            predictionInformation << " HAPPY ";
        if (outputSurprised != 0)
            predictionInformation << " SURPRISED ";
        if (outputDisgust != 0)
            predictionInformation << " DISGUST ";
        if (outputAnger != 0)
            predictionInformation << " ANGER ";
        
        putText(img, predictionInformation.str().c_str(), Point(100, 150), CV_FONT_HERSHEY_TRIPLEX, 0.5, Scalar(255,255,255), 2);
        
    }
    cout << " here" << endl;
    
    cv::imwrite("minimal.bmp", img);
    
    cv::resize(img, img, Size(800, 800), 0, 0, INTER_CUBIC);
    
    cvNamedWindow( "stasm minimal", 1 );
    cv::imshow("stasm minimal", img);
    
}

// Function to detect and draw any faces that is present in an image
void detect_and_draw( IplImage* img )
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
    
    // --- stasm code
    Mat imageIplMat = img;
    
    imwrite( path, imageIplMat );
    
    asmfind ();
}

int main()
{
    svmclassifier.svmTrain();
    
    std::string filename = "/Users/Heman/Documents/workstation/College/Classwork/Projects/VA/EmotionRecognitionVideo1.avi";
    
    bool result = true;
    
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
    if (filename.length() == 0) {
        capture.open( -1 );
    } else {
        capture.open( filename );
    }
    
    Mat frame;
    
    if( capture.isOpened() )
    {
        for(;;) {
            long loop = 0;
            
            if (loop++ % 30 == 0) {
                
                
                capture >> frame;
                
                if( !frame.empty() ) {
                    IplImage* image = cvCreateImage(cvSize(frame.cols, frame.rows), 8, 3);
                    IplImage ipltemp = frame;
                    cvCopy(&ipltemp, image);
                    
                    detect_and_draw(image);
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
    
    return 0;
}
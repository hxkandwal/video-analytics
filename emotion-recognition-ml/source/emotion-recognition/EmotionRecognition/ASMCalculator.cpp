//
//  ASMCalculator.cpp
//  EmotionRecognition
//
//  Created by Himanshu Kandwal on 5/9/16.
//  Copyright © 2016 Himanshu Kandwal. All rights reserved.
//

#include "ASMCalculator.hpp"
#include "svmClassifier.h"
#include "stasm_lib.h"

using namespace cv;
using namespace std;

// Create a string that contains the cascade name
const char* temporaryImagePath = "/Users/Heman/Documents/workstation/Developement_Studio/Xcode_Laboratory/EmotionRecognition/EmotionRecognition/EmotionRecognition/data/out/temp/temp_image.jpeg";

int pixelChangeValue = 5;
int overallFeatureChange = 5;

float baseXValue = 0;
float baseYValue = 0;

float baseArray[154];
float deltaFeaturesArray[154];

Scalar textColor = Scalar(0,0,255);

void ASMCalculator::findASMData(SvmClassifier svmclassifier, std::string imageType) {
    
    float aggregateXValue = 0;
    float aggregateYValue = 0;
    
    int changedFeaturesCount = 0;
    
    cv::Mat_<unsigned char> temporarySavedImage(cv::imread(temporaryImagePath, CV_LOAD_IMAGE_GRAYSCALE));
    
    if (!temporarySavedImage.data) {
        printf("Cannot load %s\n", temporaryImagePath);
        exit(1);
    }
    
    int faceCounts;
    float landmarks[2 * stasm_NLANDMARKS]; // x,y coords (note the 2)
    
    if (!stasm_search_single(&faceCounts, landmarks, (const char*) temporarySavedImage.data, temporarySavedImage.cols, temporarySavedImage.rows, temporaryImagePath, "/Users/Heman/Documents/workstation/Applications/opencv/opencv-2.4.11/data/testing/")) {
        printf("Error in stasm_search_single: %s\n", stasm_lasterr());
        exit(1);
    }
    
    bool baseSet = false;
    if ((baseXValue == 0 && baseYValue == 0))
        baseSet = true;
    
    if (!faceCounts) {
        printf("face not detected in %s\n", temporaryImagePath);
    }
    else {
        int index = 0;
        
        float incrementalXValue = 0;
        float incrementalYValue = 0;
        
        // draw the landmarks on the image as white dots (image is monochrome)
        
        stasm_force_points_into_image(landmarks, temporarySavedImage.cols, temporarySavedImage.rows);
        
        for (int i = 0; i < stasm_NLANDMARKS; i++) {
            temporarySavedImage(cvRound(landmarks[i*2+1]), cvRound(landmarks[i*2])) = 255;
            
            if (baseSet == true) {
                baseArray [index ++] = cvRound(landmarks[i*2+1]);
                baseArray [index ++] = cvRound(landmarks[i*2]);
                
                baseXValue += cvRound(landmarks[i*2+1]);
                baseYValue += cvRound(landmarks[i*2]);
                
                if (incrementalXValue == 0 && incrementalYValue ==0) {
                    incrementalXValue = cvRound(landmarks[i*2+1]);
                    incrementalYValue = cvRound(landmarks[i*2]);
                }
            }
            else {
                bool set = false;
                int changeFromBase = baseArray [index] - cvRound(landmarks[i*2+1]);
                deltaFeaturesArray[index ++] = changeFromBase;
                
                if (changeFromBase > pixelChangeValue) {
                    set = true;
                    changedFeaturesCount ++;
                }
                
                changeFromBase = baseArray [index] - cvRound(landmarks[i*2]);
                deltaFeaturesArray[index ++] = changeFromBase;
                
                if (set == false && changeFromBase > pixelChangeValue) {
                    changedFeaturesCount ++;
                }
                
                aggregateXValue += cvRound(landmarks[i*2+1]);
                aggregateYValue += cvRound(landmarks[i*2]);
                
                if (incrementalXValue == 0 && incrementalYValue ==0) {
                    incrementalXValue = cvRound(landmarks[i*2+1]);
                    incrementalYValue = cvRound(landmarks[i*2]);
                } else {
                    line(temporarySavedImage, Point(incrementalYValue, incrementalXValue), Point(cvRound(landmarks[i*2]), cvRound(landmarks[i*2+1])), Scalar(0, 0, 255));
                    
                    incrementalXValue = cvRound(landmarks[i*2+1]);
                    incrementalYValue = cvRound(landmarks[i*2]);
                }
            }
        }
        
        float difference = (fabs (baseXValue - aggregateXValue) + fabs (baseYValue - aggregateYValue));
        
        std::cout << "baseXValue : " << baseXValue << " , baseYValue : " << baseYValue << endl;
        std::cout << "aggregateXValue : " << aggregateXValue << " , aggregateYValue : " << aggregateYValue << endl;
        std::cout << "  = difference : " << difference << endl;
        
        cv::Mat queryFeature = cv::Mat(1, 154, CV_32F, deltaFeaturesArray);
        
        ostringstream diffConsole;
        diffConsole <<  difference << " , " << changedFeaturesCount;
        putText(temporarySavedImage, diffConsole.str().c_str(), Point(100, 100), CV_FONT_HERSHEY_TRIPLEX, 0.5, textColor, 2);
        
        ostringstream peakInformation;
        if (changedFeaturesCount > overallFeatureChange)
            peakInformation <<  "------->> PEAK ";
        else
            peakInformation <<  "------->> NORMAL ";
        
        putText(temporarySavedImage, peakInformation.str().c_str(), Point(100, 130), CV_FONT_HERSHEY_TRIPLEX, 0.5, textColor, 2);
        
        bool happyFound = false;
        bool found = false;
        ostringstream emotionEstimateConsole;
        emotionEstimateConsole <<  "EMOTION DETECTED : " ;
        
        float isHappy = svmclassifier.isHappy(queryFeature);
        if (isHappy != 0) {
            happyFound = true;
            found = true;
            emotionEstimateConsole << " HAPPY ";
        }
        
        float isSurprised = svmclassifier.isSurprised(queryFeature);
        if (isSurprised != 0) {
            found = true;
            emotionEstimateConsole << " SURPRISED ";
        }
        
        float isSad = svmclassifier.isSad(queryFeature);
        if (isSad != 0 && happyFound == false ) {
            found = true;
            emotionEstimateConsole << " SAD ";
        }
        
        float isDisgusted = svmclassifier.isDisgusted(queryFeature);
        if (isDisgusted != 0 && found == false) {
            found = true;
            emotionEstimateConsole << " DISGUST ";
        }
        
        float isAngry = svmclassifier.isAngry(queryFeature);
        if (isAngry != 0 && found == false) {
            found = true;
            emotionEstimateConsole << " ANGER ";
        }
        
        if (found == false)
            emotionEstimateConsole << " NEUTRAL ";
        
        putText(temporarySavedImage, emotionEstimateConsole.str().c_str(), Point(100, 160), CV_FONT_HERSHEY_TRIPLEX, 0.5, textColor, 2);
        
    }
    
    cv::imwrite("minimal.bmp", temporarySavedImage);
    
    if (imageType.find ("MOV") != std::string::npos) {
        cv::resize(temporarySavedImage, temporarySavedImage, Size(800, 800), 0, 0, INTER_CUBIC);
    }
    
    cvNamedWindow( "stasm minimal", 1 );
    cv::imshow("stasm minimal", temporarySavedImage);
}

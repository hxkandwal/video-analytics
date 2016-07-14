//
//  svmClassifier.h
//  EmotionRecognition
//
//  Created by Himanshu Kandwal on 5/8/16.
//  Copyright © 2016 Himanshu Kandwal. All rights reserved.
//

#ifndef svmClassifier_h
#define svmClassifier_h

#include <opencv/cv.h>
#include <opencv/highgui.h>     // opencv general include file
#include <opencv/ml.h>    // opencv machine learning include file

using namespace std;
using namespace cv;

class SvmClassifier {
protected:
    CvSVM* happySvm;
    CvSVM* surprisedSvm;
    CvSVM* disgustSvm;
    CvSVM* angrySvm;
    CvSVM* sadSvm;
    
public:
    float isHappy(Mat mat);
    float isSurprised(Mat mat);
    float isDisgusted(Mat mat);
    float isAngry(Mat mat);
    float isSad(Mat mat);
    
    int training();
    int training(const char* trainfile, int classNumber);
    
};

#endif /* svmClassifier_h */
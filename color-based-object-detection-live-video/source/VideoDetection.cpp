#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv/cv.h>
#include <iostream>
#include <stdio.h>
#include <cstdlib>

using namespace cv;
using namespace std;

// Scalar ORANGE_MIN = Scalar(5, 50, 50);
// Scalar ORANGE_MAX = Scalar(18, 255, 255);

Scalar ORANGE_MIN = Scalar(7, 50, 50);
Scalar ORANGE_MAX = Scalar(22, 255, 255);

void morphOps(Mat &thresh){

    //create structuring element that will be used to "dilate" and "erode" image.
    //the element chosen here is a 3px by 3px rectangle
    Mat erodeElement = getStructuringElement(MORPH_RECT, Size(3,3));
    //dilate with larger element so make sure object is nicely visible
    Mat dilateElement = getStructuringElement(MORPH_RECT, Size(5,5));
    
    erode(thresh,thresh,erodeElement);
    erode(thresh,thresh,erodeElement);
}

int performColoring = 0;

int main(int argc, char** argv)
{
    int dp=1 , mindist=100, param1=300, param2=60, minradius=0, maxradius=0;
    IplImage* frame;

    performColoring = atoi(argv[1]);
    
    CvCapture* capture = cvCaptureFromCAM(0);
    
    if (!capture) {
        printf("Capture failure\n");
        return -1;
    }

    while (true)
    {
        frame = cvQueryFrame(capture);

        if (!frame) 
            break;

        Mat imgOriginal(frame);

        Mat orangeDetectedImage, imgHSV;
        cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);

            // // remove skin tone
            // Mat alpha, dst;   
            // inRange(imgHSV, Scalar(0, 40, 60), Scalar(20, 150, 255), alpha);    
            // bitwise_not(alpha,alpha);


            // //split source  
            // Mat bgr[3];   
            // split(imgHSV, bgr);   

            // //Merge to final image including alpha   
            // Mat tmp[4] = {bgr[0],bgr[1],bgr[2], alpha};   
            // merge(tmp, 4, imgHSV);   

        
        inRange(imgHSV, ORANGE_MIN, ORANGE_MAX, orangeDetectedImage);
        morphOps(orangeDetectedImage);

        vector< vector<Point> > contours;
        vector<Vec4i> hierarchy;
        vector<Point> approx;

        findContours(orangeDetectedImage.clone(), contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));

        for (int i = 0; i < contours.size(); i++)
        {
            approxPolyDP(cv::Mat(contours[i]),  approx,  cv::arcLength(cv::Mat(contours[i]), true) * 0.02, true);

            if (std::fabs(cv::contourArea(contours[i])) < 100 || !cv::isContourConvex(approx))
                continue;

            cout << "shape detected !" << approx.size() << endl;

            // Detect and label circles
            if (approx.size() >= 5) 
            {
                // Detect and label circles
                double area = cv::contourArea(contours[i]);
                cv::Rect r = cv::boundingRect(contours[i]);
                int radius = r.width/2;

                if (std::abs(1 - ((double)r.width / r.height)) <= 0.2 &&  std::abs(1 - (area / (CV_PI * std::pow(radius, 2)))) <= 0.2) {
                    cout << "circle detected !" << endl;
                    int xpos = r.x + (r.width/ 2);
                    int ypos = r.y + (r.height/ 2);

                    Point center = Point(xpos, ypos);
                    
                    ostringstream convert;
                    convert << xpos << " , " << ypos << " radius : " << radius;

                    circle(imgOriginal, center, radius, Scalar(0, 255, 0), 3, 8, 0 );
                    rectangle(imgOriginal, center + Point(-radius, -radius), center + Point(radius, radius), Scalar(0, 0, 255), 3);
                    putText(imgOriginal, convert.str().c_str(), center , 1, 1, Scalar(0,255,0));

                    if (performColoring == 1) {
                        drawContours(imgOriginal, contours, i, Scalar(85, 0, 0), CV_FILLED, 8, hierarchy);
                    }
                }
                
            }
       
        }

        imshow("Finding Orange : orangeDetectedImage", orangeDetectedImage);
        imshow("Finding Orange : imgOriginal", imgOriginal);
        //imshow("Finding Orange : imgHSV", imgHSV);
        
        int c=cvWaitKey(1);

        if (char(c) == 27)
            break;

    }

    return 0;
}
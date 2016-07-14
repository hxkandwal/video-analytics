#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cstdlib>

using namespace cv;
using namespace std;


char window_name1[] = "Original Image";
char window_name2[] = "OrangeOnly Image";
int offset = 0;

Mat findHSVColor(const Mat& srcImage,  int rng=15) {
    
    // Make sure that your input image uses the channel order B, G, R (check not implemented).
    Mat inputClone = srcImage.clone();
    Mat imgThreshold, imgThreshold0, imgThreshold1;

    // In the HSV-color space the color 'orange' is located around the H-value 0 and also around the
    // H-value 180. That is why you need to threshold your image twice and the combine the results.
    inRange(inputClone, Scalar(0, 21, 185, 0), Scalar(rng, 255, 255, 0), imgThreshold0);

    if (rng > 0) {
        inRange(inputClone, Scalar(180-15, 21, 185, 0), Scalar(180, 255, 255, 0), imgThreshold1);
        bitwise_or(imgThreshold0, imgThreshold1, imgThreshold);
    } else {
        imgThreshold = imgThreshold0;
    }

    return imgThreshold;
}

int main( int argc, char** argv) {

    /// Load the source image

    Mat srcImage = imread(argv[1], 1);

    offset = atoi(argv[2]);

    if (! srcImage.data ) {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    namedWindow(window_name1, WINDOW_AUTOSIZE );
    imshow("Original Image", srcImage);

    Mat orangeOnly = findHSVColor(srcImage);
    namedWindow( window_name2, WINDOW_AUTOSIZE );
    imshow("orangeOnly", orangeOnly);

    imwrite( "image-detected-orange-50-hsv.jpg", orangeOnly );

    waitKey();

    return 0;
}
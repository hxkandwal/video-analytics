I#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
I

using namespace cv;
using namespace std;

char window_name1[] = "Original Image";
char window_name2[] = "OrangeOnly Image";
int offset = 0;

Mat orangeFilter(const Mat& srcImage) {
    
    Mat orangeOnly;
    
    if (offset == 50) {
        inRange(srcImage, Scalar(32, 165, 218), Scalar(88, 219, 255), orangeOnly);
    }
    else if (offset == 100) {
        inRange(srcImage, Scalar(142, 233, 247), Scalar(208, 255, 255), orangeOnly);
    }
    else {
        inRange(srcImage, Scalar(0, 90, 200), Scalar(10, 150, 255), orangeOnly);
    }

    return orangeOnly;
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

    Mat orangeOnly = orangeFilter(srcImage);
    namedWindow( window_name2, WINDOW_AUTOSIZE );
    imshow("orangeOnly", orangeOnly);
    imwrite( "image-detected-orange-100-rgb.jpg", orangeOnly);

    waitKey();

    return 0;
}
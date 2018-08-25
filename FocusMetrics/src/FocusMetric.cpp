//============================================================================
// Name        : Internship.cpp
// Author      : Naga Anjaneyulu
// Version     :
// Copyright   : @All rights reserved 2018.
// Description : Hello World in C++, Ansi-style
//============================================================================

//============================================================================
// Name        : FocusMetrics.cpp
// Author      : Naga Anjaneyulu
// Version     :
// Copyright   : @All rights are reserved.
// Description : Computing Focus metrics for an image .
//============================================================================

#include <iostream>
#include <stdint.h>
#include <opencv2/opencv.hpp>
#define _UNIT32_TYPE_ long unsigned int
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
 // Read the image file
    Mat dst;
    Mat image = imread("C:/Users/anji/eclipse-workspace/Internship/Images/img_1.jpg");

    if (image.empty())
    {
      cout << "Could not open or find the image" << endl;
      cin.get();
      return -1;
    }

    cvtColor(image, image, COLOR_BGR2GRAY);


// Brenner's Algorithm

 /*	DV(1:M-2,:) = Image(3:end,:)-Image(1:end-2,:);
 	DH(:,1:N-2) = Image(:,3:end)-Image(:,1:end-2);
 	FM = max(DH, DV);
 	FM = FM.^2;
 	FM = mean2(FM);*/
 	cv::Size s = image.size();
 	int rows = s.height;
 	int cols = s.width;
 	Mat DH = Mat(rows,cols, CV_64F, double(0));
 	Mat DV = Mat(rows,cols, CV_64F, double(0));
   /* DV.rowRange(0,rows-2).colRange(0,cols) = image.rowRange(2,rows).colRange(0,cols) - image.rowRange(0,rows-2).colRange(0,cols);
    DH.rowRange(0,rows).colRange(0,cols-2) = image.rowRange(0,rows).colRange(2,cols) - image.rowRange(0,rows).colRange(0,cols-2);*/
    cv::subtract(image.rowRange(2,rows).colRange(0,cols),image.rowRange(0,rows-2).colRange(0,cols), DV.rowRange(0,rows-2).colRange(0,cols));
    cv::subtract(image.rowRange(0,rows).colRange(2,cols),image.rowRange(0,rows).colRange(0,cols-2), DH.rowRange(0,rows).colRange(0,cols-2));

    Mat FM =  cv::max(DH,DV);
    FM = FM.mul(FM);
    cv::Scalar tempVal = mean( FM );
    float myMatMean = tempVal.val[0];
    cout << "Focus Measure is " <<endl;
    cout << myMatMean << endl;

   return 0;
}



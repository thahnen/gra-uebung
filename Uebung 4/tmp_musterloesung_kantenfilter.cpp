#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <ctime>

using namespace std;
using namespace cv;


int main(int argc, char *argv[])
{
  double time1=0.0, tstart; 
  //Einlesen des Bildes
  Mat img =cv::imread("muenzen.bmp",0); 
  Mat color;
  cvtColor(img, color, CV_GRAY2BGR);
  if( !img.data )
  {   
	cout<<"Bild fehlt"<<endl;
	return -1; 
  }
  //Erzeugen eines Fensters und Anzeige des Bildes
  imshow("Original", img );
  GaussianBlur(img, img, Size(5, 5), 2.0);
    
    
  Mat dx, dy, dxx, dyy, betrag, show, bin;
  Sobel(img, dx, CV_32F, 1, 0);
  Sobel(img, dy, CV_32F, 0, 1);
  pow(dx, 2, dxx);
  pow(dy, 2, dyy);
  add(dxx, dyy, betrag);
  pow(betrag, 0.5, betrag);
  double minVal, maxVal;
  minMaxLoc(betrag, &minVal, &maxVal);
  convertScaleAbs(betrag, show, 255.0 / (maxVal - minVal), -minVal*255.0 / (maxVal - minVal));
  imshow("Betrag", show );
  threshold(show, show, 100, 255, CV_THRESH_BINARY);
  imshow("Bin", show);
    
    
  for (int i = 0; i < img.rows; i = i + 5)
	  for (int j = 0; j < img.cols; j = j + 5)
	  {
		  if (show.at<uchar>(i, j) == 255)
		  {
			  float x = dx.at<float>(i, j);
			  float y = dy.at<float>(i, j);
			  arrowedLine(color, cv::Point(j, i), cv::Point(j + x /10, i + y /10), Scalar(0, 0, 255));
		  }
	  }
    
    
  Scharr(img, dx, CV_32F, 1, 0);
  Scharr(img, dy, CV_32F, 0, 1);
    
    
  for (int i = 0; i < img.rows; i = i + 5)
	  for (int j = 0; j < img.cols; j = j + 5)
	  {
		  if (show.at<uchar>(i, j) == 255)
		  {
			  float x = dx.at<float>(i, j);
			  float y = dy.at<float>(i, j);
			  arrowedLine(color, cv::Point(j, i), cv::Point(j + x /10, i + y /10), Scalar(0, 255, 0));
		  }
	  }
  //Warten auf Tastendruck
  imshow("Gradientenrichtung", color);
  cvWaitKey(0);
  return 0;
}



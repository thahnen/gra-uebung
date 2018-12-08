#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cmath>
#include <iostream>

using namespace cv;

void image_linear(Mat &img, Mat &nimg)
//Lineare Skalierung des Ergebnisses
{
	double minVal, maxVal;
	minMaxLoc(img, &minVal, &maxVal, 0, 0, 0); // Suche nach Minimum und Maximum
	convertScaleAbs(img,nimg,255.0/(maxVal-minVal),-minVal*255.0/(maxVal-minVal));
}

void shiftDFT(Mat &img )
{
	//Vertauschen der Quadranten
    int cx = img.cols/2;
    int cy = img.rows/2;
    Mat tmp;
    Mat q0(img, Rect(0, 0, cx, cy));
    Mat q1(img, Rect(cx, 0, cx, cy));
    Mat q2(img, Rect(0, cy, cx, cy));
    Mat q3(img, Rect(cx, cy, cx, cy));
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);   
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);
}

int main(int argc, char *argv[])
{
  Mat orgimg =imread("blumen.bmp",0); 
  imshow("Original", orgimg );
    Mat temp =imread("blumen_template.bmp",0);
    imshow("Template", temp );
    
  //Umwandeln in komplexe Zahl, Realteil = Bild, Imaginärteil = 0
  Mat real_imag[] = {Mat_<float>(orgimg), Mat::zeros(orgimg.size(), CV_32F)};
  Mat complexImg, complexTemp;
    Mat erg(orgimg.rows,orgimg.cols,CV_32F,Scalar(0));
    
  merge(real_imag, 2, complexImg); 
  dft(complexImg, complexImg);
  real_imag[0]=Scalar(0);
    
  for (int i = 0; i < temp.rows; i++)
	  for (int j = 0; j < temp.cols; j++) {
		  real_imag[0].at<float>(i, j) = (float)temp.at<uchar>(i, j);
	  }
    
  merge(real_imag, 2, complexTemp); 
  dft(complexTemp, complexTemp); 
  mulSpectrums( complexImg, complexTemp, complexImg, DFT_ROWS, true ); // Multipliziert Bild-FFT mit konjugiert komplexer Template-FFT
  idft( complexImg, complexImg, DFT_SCALE);
  split(complexImg,real_imag);
  normalize(real_imag[0], real_imag[0], 0, 1, CV_MINMAX);
    
  imshow("Ergebnis1", real_imag[0] );
  waitKey(0);
    
  
  for ( int i = 0; i < orgimg.rows-temp.rows-1; i++ )
		for (int j = 0; j < orgimg.cols-temp.cols-1; j++ )
			for (int k = 0; k < temp.rows; k++)
				for (int l = 0; l < temp.cols; l++)
					erg.at<float>(i, j) += (float)orgimg.at<uchar>(i + k, j + l) * temp.at<uchar>(k, l);
  
  normalize(erg, orgimg, 0, 1, CV_MINMAX);
    
  imshow("Ergebnis2", orgimg);
  waitKey(0);
  return 0;
}


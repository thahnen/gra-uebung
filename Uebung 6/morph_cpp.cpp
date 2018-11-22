#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>



using namespace cv;

void image_linear(Mat &img, Mat &nimg)
//lineare Skalierung der Grauwerte
{
	double minVal, maxVal;
	minMaxLoc(img,&minVal,&maxVal);//Bestimmung von Minimum und Maximum
	convertScaleAbs(img, nimg, 255./(maxVal-minVal), -minVal*255./(maxVal-minVal));
}


void hit_or_miss(Mat &img, Mat &color){
//Erzeugung des Distanzbildes
	Mat dest1, dest2;
	//Erzeugung des Strukturelements
	Mat element1(7, 7, CV_8U, Scalar(0));
	circle(element1, Point(3, 3), 3, Scalar(255), -1);
	//std::cout << element1 << std::endl;
	erode(img, dest1, element1);
	imshow("Ergebnis Hit-Or-Miss1", dest1);
	bitwise_not(img, img);
	//Erzeugung des Strukturelements
	Mat element2(25, 25, CV_8U, Scalar(255));
	circle(element2, Point(12, 12), 11, Scalar(0), -1);
	imshow("Maske 2", element2);
	erode(img, dest2, element2);
	imshow("Ergebnis Hit-Or-Miss2", dest2);
	bitwise_and(dest1, dest2, dest1);
	imshow("Ergebnis Hit-Or-Miss", dest1);
	for (int i = 0; i < img.rows; i++)
		for (int j = 0; j < img.cols; j++)
		{
			if (dest1.at<uchar>(i, j) == 255)
			{
				floodFill(color, Point(j, i), Scalar(0, 0, 255), 0, Scalar(0), Scalar(0), 4);
				floodFill(dest1, Point(j, i), Scalar(127, 0, 0), 0, Scalar(0), Scalar(0), 4);
			}
		}
}

void fuellen(Mat &img, Mat &nimg ){
	Mat kimg, temp;
	//Erzeugung des Strukturelements
	Mat element=getStructuringElement(MORPH_CROSS,Size(3,3)); 
	//Erzeugen des invertierten Bildes kimg
	bitwise_not(img,kimg);
	//Setzen des Startpixels
	nimg = Scalar(0);
	nimg.at<uchar>(nimg.rows/2,nimg.cols/2)=255;	
	//Durchführung der Operationen in der Schleife, solange sich Anzahl der gesetzten Pixel ändert
	int alt, neu;
	do 
	{
		alt = countNonZero( nimg );	//Ermittlung der Anzahl der gesetzen Pixel vor der Operation
		dilate(nimg, temp, element);	//Durchführung der Dilatation
		bitwise_and( temp, kimg, nimg);	//AND-Verknüpfung zum Einschränken der Füllung auf das Objekt
		/*imshow("Test", nimg);
		waitKey(10);*/
	}while(alt != countNonZero(nimg));
	bitwise_or(img, nimg, nimg); // Verknüpfung von Füllmenge und Konturpixeln
}

int main(int argc, char *argv[])
{
  //Einlesen des zu füllenden Bildes

  Mat img = imread("binaer1.bmp",0); 
  // Anzeige des Bildes
  imshow("Original1", img );
  Mat color;
  cvtColor(img, color, CV_GRAY2RGB);
  hit_or_miss(img, color);
  imshow("Ergebnis1", color );

  img = imread("binaer2.bmp", 0);
  // Anzeige des Bildes
  imshow("Original2", img);
  Mat nimg = img.clone();
  //Füllen der Kontur und Anzeige des Ergebnisses
  fuellen(img, nimg);
  imshow("Ergebnis2", nimg);
  waitKey(0);
  return 0;
}


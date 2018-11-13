//
//  GRA-OpenCV Template für alle GRA-Übungen
//
//  Created by Tobias Hahnen on 16.10.18.
//  Copyright © 2018 Tobias Hahnen. All rights reserved.
//

// ÜBUNG 4

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace cv;
using namespace std;


void histogramm(Mat &bild, Mat &hist_bild, int hist_w, int hist_h) {
    Mat hist;
    hist_bild = Scalar(0, 0, 0);
    int hist_size = 256;
    float range[] = {0, 256};
    const float* hist_range = { range };
    calcHist(&bild, 1, 0, Mat(), hist, 1, &hist_size, &hist_range, true, false);
    int bin_w = (int)((double)hist_w/hist_size);
    normalize(hist, hist, 0, hist_bild.rows, NORM_MINMAX, -1, Mat());
    for (int i=0; i<hist_size; i++) {
        line(hist_bild, Point(bin_w*(i), hist_h-cvRound(hist.at<float>(i))), Point(bin_w*(i), hist_h), Scalar(255, 255, 255));
    }
}

void filter(Mat img, Mat &nimg, Mat mask) {
    double s, su = sum(mask).val[0];
    for (int j=mask.rows/2; j<img.rows-mask.rows/2; j++) {
        for (int i=mask.cols/2; i<img.cols-mask.cols/2; i++) {
            s = 0;
            for (int k=-mask.rows/2; k<=mask.rows/2; k++) {
                for (int l=-mask.cols/2; l<= mask.cols/2; l++) {
                    s += (int)img.at<uchar>(j+k, i+l)*mask.at<float>(k+ mask.rows/2, l+ mask.cols/2);
                }
            }
            nimg.at<uchar>(j,i) = s/su;
        }
    }
}


int main(int argc, const char * argv[]) {
    // Setup
    // Warum auch immer kein relativer Pfad geladen werden kann -.-
    Mat bild = imread("/Users/thahnen/GitHub/gra-uebung/Uebung 4/muenzen.bmp", 0);
    int hist_w = 256;
    int hist_h = 450;
    Mat hist_bild(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
    
    if (!bild.data) {
        cerr << "Bild konnte nicht geladen werden!" << endl;
        return 1;
    }
    
    
    // Vor Bearbeitung:
    Mat farbbild;
    cvtColor(bild, farbbild, CV_GRAY2BGR);
    Scalar durchschnitt, standardabweichung;
    meanStdDev(bild, durchschnitt, standardabweichung);
    cout << "\nMittlerer Grauwert (Normales Bild): " << durchschnitt[0] << endl;
    cout << "Standardabweichung (Normales Bild): " << standardabweichung[0] << endl;
    imshow("Normales Bild", bild);
    imshow("Farbbild", farbbild);
    waitKey(0);
    
    
    // Aufgabe: Rauschen entfernen
    // => Mgl. 1: Binomialfilter -> cv::
    // => Mgl. 2: Gaussfilter -> cv::GaussianBlur(...)
    // => Mgl. 3: Medianfilter -> cv::medianBlur(...)
    Mat median_bild = bild.clone();
    medianBlur(bild, median_bild, 3);
    imshow("Rauschen entfernt", median_bild);
    waitKey(0);
    
    
    // Aufgabe: Kanten mit Sobel-Operator bestimmen
    Mat sobel_bild = median_bild.clone();
    Mat dx, dy, dxx, dyy, dxxx, dyyy, sobel_complete;
    Sobel(sobel_bild, dx, CV_32F, 1, 0);
    Sobel(sobel_bild, dy, CV_32F, 0, 1);
    pow(dx, 2, dxxx);
    pow(dy, 2, dyyy);
    add(dxxx, dyyy, sobel_complete);
    pow(sobel_complete, 0.5, sobel_complete);
    
    double min, max;
    minMaxLoc(dx, &min, &max);
    convertScaleAbs(dx, dxx, 255/(max-min), -min*255/(max-min));
    minMaxLoc(dy, &min, &max);
    convertScaleAbs(dy, dyy, 255/(max-min), -min*255/(max-min));
    
    minMaxLoc(sobel_complete, &min, &max);
    convertScaleAbs(sobel_complete, sobel_complete, 255/(max-min), -min*255/(max-min));
    
    //imshow("Sobel (dx)", dxx);
    //imshow("Sobel (dy)", dyy);
    imshow("Sobel (dx & dy)", sobel_complete);
    threshold(sobel_complete, sobel_complete, 100, 255, CV_THRESH_BINARY);
    //imshow("Sobel (dx & dy) inv", sobel_complete);
    waitKey(0);
    
    
    // Aufgabe: Gradientenrichtung für jeden Pixel in 5.Reihe/5.Spalte als rote Linie
    for (int i=0; i<bild.rows; i+=5) {
        for (int j=0; j<bild.cols; j+=5) {
            if (sobel_complete.at<uchar>(i, j) == 255) {
                float x = dx.at<float>(i, j);
                float y = dy.at<float>(i, j);
                arrowedLine(farbbild, Point(j, i), Point(j+x/10, i+y/10), Scalar(0, 0, 255));
            }
        }
    }
    imshow("Gradientenrichtung", farbbild);
    waitKey(0);
    
    
    // Aufgabe: Filterung mit verbessertem Sobel-Filter
    // => cv::Scharr()
    Mat scharr_bild = median_bild.clone();
    Mat dsx, dsy, dsxx, dsyy, dsxxx, dsyyy, scharr_complete;
    Scharr(scharr_bild, dsx, CV_32F, 1, 0);
    Scharr(scharr_bild, dsy, CV_32F, 0, 1);
    pow(dsx, 2, dsxxx);
    pow(dsy, 2, dsyyy);
    add(dsxxx, dsyyy, scharr_complete);
    pow(scharr_complete, 0.5, scharr_complete);
    
    minMaxLoc(dsx, &min, &max);
    convertScaleAbs(dsx, dsxx, 255/(max-min), -min*255/(max-min));
    minMaxLoc(dsy, &min, &max);
    convertScaleAbs(dsy, dsyy, 255/(max-min), -min*255/(max-min));
    
    minMaxLoc(scharr_complete, &min, &max);
    convertScaleAbs(scharr_complete, scharr_complete, 255/(max-min), -min*255/(max-min));
    
    //imshow("Scharr (dx)", dsxx);
    //imshow("Scharr (dy)", dsyy);
    imshow("Scharr (dx & dy)", scharr_complete);
    threshold(scharr_complete, scharr_complete, 100, 255, CV_THRESH_BINARY);
    //imshow("Scharr (dx & dy) inv", scharr_complete);
    waitKey(0);
    
    
    // Aufgabe: Gradientenrichtung für jeden Pixel in 5.Reihe/5.Spalte als grüne Linie
    for (int i=0; i<bild.rows; i+=5) {
        for (int j=0; j<bild.cols; j+=5) {
            if (scharr_complete.at<uchar>(i, j) == 255) {
                float x = dsx.at<float>(i, j);
                float y = dsy.at<float>(i, j);
                arrowedLine(farbbild, Point(j, i), Point(j+x/100, i+y/100), Scalar(255, 0, 0));
            }
        }
    }
    imshow("Gradientenrichtung 2", farbbild);
    waitKey(0);
    
    
    return 0;
}

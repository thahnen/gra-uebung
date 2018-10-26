//
//  GRA-OpenCV Template für alle GRA-Übungen
//
//  Created by Tobias Hahnen on 16.10.18.
//  Copyright © 2018 Tobias Hahnen. All rights reserved.
//

// ÜBUNG 2

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define DEBUG true

using namespace cv;
using namespace std;

void histogramm(Mat &bild, Mat &hist_bild, int hist_w, int hist_h, Scalar color) {
    Mat hist;
    int hist_size = 256;
    float range[] = {0, 256};
    const float* hist_range = { range };
    calcHist(&bild, 1, 0, Mat(), hist, 1, &hist_size, &hist_range, true, false);
    int bin_w = (int)((double)hist_w/hist_size);
    normalize(hist, hist, 0, hist_bild.rows, NORM_MINMAX, -1, Mat());
    for (int i=0; i<hist_size; i++) {
        line(hist_bild, Point(bin_w*(i), hist_h-cvRound(hist.at<float>(i))), Point(bin_w*(i), hist_h), color);
    }
}

int main(int argc, const char * argv[]) {
    // Setup
    // Warum auch immer kein relativer Pfad geladen werden kann -.-
    Mat bild = imread("/Users/thahnen/GitHub/gra-uebung/Uebung 2/London.bmp", 0);
    int hist_w = 256;
    int hist_h = 400;
    Mat hist;
    Mat hist_bild(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
    
    if (!bild.data) {
        cerr << "Bild konnte nicht geladen werden!" << endl;
        return 1;
    }
    
    
    // 1. Aufgabe
    Scalar durchschnitt, standardabweichung;
    meanStdDev(bild, durchschnitt, standardabweichung);
    cout << "\nMittlerer Grauwert (Normales Bild): " << durchschnitt[0] << endl;
    cout << "Standardabweichung (Normales Bild): " << standardabweichung[0] << endl;
    if (DEBUG) imshow("Normales Bild", bild);
    hist_bild = Scalar(0, 0, 0);
    histogramm(bild, hist_bild, hist_w, hist_h, Scalar(255, 255, 255));
    imshow("Hist: Normales Bild", hist_bild);
    waitKey(0);
    
    // a) lineare Skalierung (mittels Look-Up-Table)
    Mat ls_bild;
    double ls_min, ls_max;
    minMaxLoc(bild, &ls_min, &ls_max);
    Mat ls_LUT(1, 256, CV_8U);
    uchar* p = ls_LUT.ptr();
    for (int i=ls_min; i<ls_max; i++) {
        // g'(g) =(g-g_min)*((w_max-w_min)/(g_max-g_min))
        // g=i - g_min=ls_min - g_max=ls_max - w_min=0 - w_max=255
        p[i] = (i-ls_min)*(255/(ls_max-ls_min));
    }
    LUT(bild, ls_LUT, ls_bild);
    
    meanStdDev(ls_bild, durchschnitt, standardabweichung);
    cout << "\nMittlerer Grauwert (Lineare Skalierung): " << durchschnitt[0] << endl;
    cout << "Standardabweichung (Lineare Skalierung): " << standardabweichung[0] << endl;
    if (DEBUG) imshow("Lineare Skalierung", ls_bild);
    hist_bild = Scalar(0, 0, 0);
    histogramm(ls_bild, hist_bild, hist_w, hist_h, Scalar(0, 255, 0));
    imshow("Hist: Lineare Skalierung", hist_bild);
    waitKey(0);
    
    
    // b) Gamma-Transformation
    Mat gt_bild = bild;
    double gamma = 0.5;
    double min, max;
    uchar lut[256]; // Nach Musterlösung; auch wie oben über LUT() machbar, ist effizienter!
    minMaxLoc(gt_bild, &min, &max);
    
    for (int i=min; i<max; i++) {
        lut[i]=(int)(255.0*pow(i/255.0 ,gamma));
    }
    
    for (int i=0; i<gt_bild.rows; i++) {
        for (int j=0; j<gt_bild.cols; j++) {
            gt_bild.at<uchar>(i, j) = lut[bild.at<uchar>(i, j)];
        }
    }
    
    meanStdDev(gt_bild, durchschnitt, standardabweichung);
    cout << "\nMittlerer Grauwert (Gamma-Transformation): " << durchschnitt[0] << endl;
    cout << "Standardabweichung (Gamma-Transformation): " << standardabweichung[0] << endl;
    if (DEBUG) imshow("Gamma-Transformation", gt_bild);
    hist_bild = Scalar(0, 0, 0);
    histogramm(gt_bild, hist_bild, hist_w, hist_h, Scalar(0, 0, 255));
    imshow("Hist: Gamma-Transformation", hist_bild);
    waitKey(0);
    
    
    // c) Histogrammausgleich
    Mat ha_bild;
    equalizeHist(bild, ha_bild); // In der Musterlösung auch anders machbar!
    
    meanStdDev(ha_bild, durchschnitt, standardabweichung);
    cout << "\nMittlerer Grauwert (Histogrammausgleich): " << durchschnitt[0] << endl;
    cout << "Standardabweichung (Histogrammausgleich): " << standardabweichung[0] << endl;
    if (DEBUG) imshow("Histogrammausgleich", ha_bild);
    hist_bild = Scalar(0, 0, 0);
    histogramm(ha_bild, hist_bild, hist_w, hist_h, Scalar(255, 0, 0));
    imshow("Hist: Histogrammausgleich", hist_bild);
    waitKey(0);
    
    
    return 0;
}

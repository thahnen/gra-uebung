//
//  GRA-OpenCV Template für alle GRA-Übungen
//
//  Created by Tobias Hahnen on 16.10.18.
//  Copyright © 2018 Tobias Hahnen. All rights reserved.
//

// ÜBUNG 3

#include <iostream>
#include <ctime>
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
    Mat bild = imread("/Users/thahnen/GitHub/gra-uebung/Uebung 3/London.bmp", 0);
    Mat n_bild, temp;
    int hist_w = 256;
    int hist_h = 450;
    Mat hist_bild(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
    
    if (!bild.data) {
        cerr << "Bild konnte nicht geladen werden!" << endl;
        return 1;
    }
    
    // 3x3-Maske erstellen aus 3x1 sowie 1x3
    float m3[3] = {1, 2, 3};
    Mat M3_1(3, 1, CV_32F, m3);
    Mat M1_3(1, 3, CV_32F, m3);
    Mat mask3_3;
    gemm(M3_1, M1_3, 1, noArray(), 0, mask3_3);
    
    // 7x7-Maske erstellen aus 7x1 sowie 1x7
    float m7[7] {1, 6, 15, 20, 15, 6, 1};
    Mat M7_1(7, 1, CV_32F, m7); // auch für seperate Anwendung
    Mat M1_7(1, 7, CV_32F, m7); // auch für seperate Anwendung
    Mat mask7x7;
    gemm(M7_1, M1_7, 1, noArray(), 0, mask7x7);
    
    // Zeitmessung
    clock_t begin, end;
    double zeitverbrauch;
    
    
    // Vor Bearbeitung:
    Scalar durchschnitt, standardabweichung;
    meanStdDev(bild, durchschnitt, standardabweichung);
    cout << "\nMittlerer Grauwert (Normales Bild): " << durchschnitt[0] << endl;
    cout << "Standardabweichung (Normales Bild): " << standardabweichung[0] << endl;
    if (DEBUG) imshow("Normales Bild", bild);
    hist_bild = Scalar(0, 0, 0);
    histogramm(bild, hist_bild, hist_w, hist_h, Scalar(255, 255, 255));
    imshow("Hist: Normales Bild", hist_bild);
    waitKey(0);
    
    
    // 1) 3-fache 3x3-Filterung
    n_bild = bild.clone();
    temp = bild.clone();
    begin = clock();
    filter(bild, n_bild, mask3_3);
    filter(n_bild, temp, mask3_3);
    filter(temp, n_bild, mask3_3);
    end = clock();
    zeitverbrauch = double(end-begin)/CLOCKS_PER_SEC;
    cout << "\n Zeit für 3-fache 3x3-Filterung (in s): " << zeitverbrauch << endl;
    if (DEBUG) imshow("3-fache 3x3-Filterung", temp);
    hist_bild = Scalar(0, 0, 0);
    histogramm(temp, hist_bild, hist_w, hist_h, Scalar(255, 255, 255));
    imshow("Hist: 3x3-Filterung", hist_bild);
    waitKey(0);
    
    
    // 2) 1-fache 7x7-Filterung
    n_bild = bild.clone();
    begin = clock();
    filter(bild, n_bild, mask7x7);
    end = clock();
    zeitverbrauch = double(end-begin)/CLOCKS_PER_SEC;
    cout << "\n Zeit für 1-fache 7x7-Filterung (in s): " << zeitverbrauch << endl;
    if (DEBUG) imshow("1-fache 7x7-Filterung", n_bild);
    hist_bild = Scalar(0, 0, 0);
    histogramm(n_bild, hist_bild, hist_w, hist_h, Scalar(255, 255, 255));
    imshow("Hist: 7x7-Filterung", hist_bild);
    waitKey(0);
    
    
    // 3) Seperat 7x1- und 1x7-Filterung
    n_bild = bild.clone();
    begin = clock();
    filter(bild, n_bild, M7_1);
    filter(n_bild, bild, M1_7);
    end = clock();
    zeitverbrauch = double(end-begin)/CLOCKS_PER_SEC;
    cout << "\n Zeit für 7x1- und 1x7-Filterung (in s): " << zeitverbrauch << endl;
    if (DEBUG) imshow("7x1- und 1x7-Filterung", bild);
    hist_bild = Scalar(0, 0, 0);
    histogramm(bild, hist_bild, hist_w, hist_h, Scalar(255, 255, 255));
    imshow("Hist: 7x1- und 1x7-Filterung", hist_bild);
    waitKey(0);
    
    
    return 0;
}

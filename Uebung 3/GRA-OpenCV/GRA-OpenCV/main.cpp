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
#include "definitions.h"

using namespace cv;
using namespace std;


int main(int argc, const char * argv[]) {
    // Setup
    // Warum auch immer kein relativer Pfad geladen werden kann -.-
    Mat bild = imread("/Users/thahnen/GitHub/gra-uebung/Uebung 3/London.bmp", 0);
    Mat n_bild, temp;
    
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
    imshow("Normales Bild", bild);
    imshow("Hist: Normales Bild", histogramm(bild));
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
    imshow("3-fache 3x3-Filterung", temp);
    imshow("Hist: 3x3-Filterung", histogramm(temp));
    waitKey(0);
    
    
    // 2) 1-fache 7x7-Filterung
    n_bild = bild.clone();
    begin = clock();
    filter(bild, n_bild, mask7x7);
    end = clock();
    zeitverbrauch = double(end-begin)/CLOCKS_PER_SEC;
    cout << "\n Zeit für 1-fache 7x7-Filterung (in s): " << zeitverbrauch << endl;
    imshow("1-fache 7x7-Filterung", n_bild);
    imshow("Hist: 7x7-Filterung", histogramm(n_bild));
    waitKey(0);
    
    
    // 3) Seperat 7x1- und 1x7-Filterung
    n_bild = bild.clone();
    begin = clock();
    filter(bild, n_bild, M7_1);
    filter(n_bild, bild, M1_7);
    end = clock();
    zeitverbrauch = double(end-begin)/CLOCKS_PER_SEC;
    cout << "\n Zeit für 7x1- und 1x7-Filterung (in s): " << zeitverbrauch << endl;
    imshow("7x1- und 1x7-Filterung", bild);
    imshow("Hist: 7x1- und 1x7-Filterung", histogramm(bild));
    waitKey(0);
    
    
    return 0;
}

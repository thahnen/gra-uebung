//
//  GRA-OpenCV Template für alle GRA-Übungen
//
//  Created by Tobias Hahnen on 16.10.18.
//  Copyright © 2018 Tobias Hahnen. All rights reserved.
//

// ÜBUNG 5

#define _USE_MATH_DEFINES   // dunno what tis dos :o
#include <iostream>
#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "definitions.h"


using namespace cv;
using namespace std;


int main(int argc, const char * argv[]) {
    // Setup
    // Warum auch immer kein relativer Pfad geladen werden kann -.-
    Mat bild = imread("/Users/thahnen/GitHub/gra-uebung/Uebung 5/schrift.bmp", 0);
    if (!bild.data) {
        cerr << "Bild konnte nicht geladen werden!" << endl;
        return 1;
    }
    
    
    // Vor Bearbeitung:
    Scalar durchschnitt, standardabweichung;
    meanStdDev(bild, durchschnitt, standardabweichung);
    cout << "\nMittlerer Grauwert (Normales Bild): " << durchschnitt[0] << endl;
    cout << "Standardabweichung (Normales Bild): " << standardabweichung[0] << endl;
    imshow("Normales Bild", bild);
    imshow("Hist: Normales Bild", histogramm(bild));
    waitKey(0);
    
    
    // Lösung nach Musterlösung, keine Struktur nach Übungsaufgabe erkennbar
    Scalar s = mean(bild);
    Mat binaer_bild, binaer_hell_bild, diff, med;
    threshold(bild, binaer_bild, s.val[0], 255, CV_THRESH_BINARY);
    imshow("Binaerbild", binaer_bild);
    waitKey(0);
    
    medianBlur(bild, med, 21);
    subtract(med, bild, diff, noArray());
    threshold(diff, binaer_hell_bild, 15, 255, CV_THRESH_BINARY);
    imshow("Binaerbild (Helligkeitskorrektur)", binaer_hell_bild);
    waitKey(0);
    
    Mat labels, stats, centroids, grenzen;
    int anzahl_labels = connectedComponentsWithStats(binaer_hell_bild, labels, stats, centroids);
    cvtColor(bild, grenzen, CV_GRAY2BGR);
    vector<Vec3b> colors(anzahl_labels);
    colors[0] = Vec3b(0, 0, 0);
    for (int i=1; i<stats.rows; i++) {
        int x = stats.at<int>(Point(0,i));
        int y = stats.at<int>(Point(1,i));
        int w = stats.at<int>(Point(2,i));
        int h = stats.at<int>(Point(3,i));
        Rect rect(x, y, w, h);
        rectangle(grenzen, rect, Scalar(255, 0, 0));
        colors[i] = Vec3b((rand() & 255), (rand() & 255), (rand() & 255));
    }
    imshow("Segmentierte Regionsgrenzen", grenzen);
    waitKey(0);
    
    grenzen = Vec3b(0, 0, 0);
    for (int y=0; y<grenzen.rows; ++y) {
        for (int x=0; x<grenzen.cols; ++x) {
            grenzen.at<Vec3b>(y, x) = colors[labels.at<int>(y, x)];
        }
    }
    imshow("Segmentierte Objekte", grenzen);
    waitKey(0);
    
    
    return 0;
}

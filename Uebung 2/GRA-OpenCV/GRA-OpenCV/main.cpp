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

using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    // Setup
    // Warum auch immer kein relativer Pfad geladen werden kann -.-
    Mat bild = imread("/Users/thahnen/GitHub/gra-uebung/Uebung 2/London.bmp", 0);
    
    if (!bild.data) {
        cerr << "Bild konnte nicht geladen werden!" << endl;
        return 1;
    }
    
    
    // 1. Aufgabe
    Scalar durchschnitt, standardabweichung;
    meanStdDev(bild, durchschnitt, standardabweichung);
    cout << "Mittlerer Grauwert (Normales Bild): " << durchschnitt[0] << endl;
    cout << "Standardabweichung (Normales Bild): " << standardabweichung[0] << endl;
    imshow("Normales Bild", bild);
    waitKey(0);
    
    // a) lineare Skalierung (mittels Look-Up-Table)
    Mat ls_bild;
    double ls_min, ls_max;
    minMaxLoc(bild, &ls_min, &ls_max);
    Mat ls_LUT(1, 256, CV_8U);
    uchar* p = ls_LUT.ptr();
    for (int i=0; i<256; i++) {
        // g'(g) =(g-g_min)*((w_max-w_min)/(g_max-g_min))
        // g=i - g_min=ls_min - g_max=ls_max - w_min=0 - w_max=255
        p[i] = (i-ls_min)*(255/(ls_max-ls_min)); // darf das überhaupt unter 0 kommen?
    }
    LUT(bild, ls_LUT, ls_bild);
    
    meanStdDev(ls_bild, durchschnitt, standardabweichung);
    cout << "Mittlerer Grauwert (Lineare Skalierung): " << durchschnitt[0] << endl;
    cout << "Standardabweichung (Lineare Skalierung): " << standardabweichung[0] << endl;
    imshow("Lineare Skalierung", ls_bild);
    waitKey(0);
    
    
    // b) Gamma-Transformation
    // TODO: irgendwie noch nicht so richtig oder?
    Mat gt_bild = bild;
    double min, max;
    minMaxLoc(gt_bild, &min, &max);
    
    for (int i=0; i<gt_bild.rows; i++) {
        for (int j=0; j<gt_bild.cols; j++) {
            // Gammakorrektur Gespreitzt (<1), Gestaucht (>1), Linear (=1)
            // ! Gespreitzt funktioniert irgendwie nicht !
            gt_bild.at<uchar>(i, j) = max * pow((gt_bild.at<uchar>(i, j)/ max), 1);
        }
    }
    
    meanStdDev(gt_bild, durchschnitt, standardabweichung);
    cout << "Mittlerer Grauwert (Gamma-Transformation): " << durchschnitt[0] << endl;
    cout << "Standardabweichung (Gamma-Transformation): " << standardabweichung[0] << endl;
    imshow("Gamma-Transformation", gt_bild);
    waitKey(0);
    
    
    // c) Histogrammausgleich
    Mat ha_bild;
    equalizeHist(bild, ha_bild);
    
    meanStdDev(ha_bild, durchschnitt, standardabweichung);
    cout << "Mittlerer Grauwert (Histogrammausgleich): " << durchschnitt[0] << endl;
    cout << "Standardabweichung (Histogrammausgleich): " << standardabweichung[0] << endl;
    imshow("Histogrammausgleich", ha_bild);
    waitKey(0);
    
    
    // d) Kontrastanpassung mit Quantilen s_low/ s_high = 10%
    // TODO: herausfinden, was gemeint ist!
    Mat ka_bild = bild; // muss dann noch geändert werden!
    
    meanStdDev(ka_bild, durchschnitt, standardabweichung);
    cout << "Mittlerer Grauwert (Kontrastanpassung): " << durchschnitt[0] << endl;
    cout << "Standardabweichung (Kontrastanpassung): " << standardabweichung[0] << endl;
    imshow("Kontrastanpassung (fehlt noch!)", ka_bild);
    waitKey(0);
    
    
    return 0;
}

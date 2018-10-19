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
    Mat ls_bild = bild;
    
    meanStdDev(ls_bild, durchschnitt, standardabweichung);
    cout << "Mittlerer Grauwert (Lineare Skalierung): " << durchschnitt[0] << endl;
    cout << "Standardabweichung (Lineare Skalierung): " << standardabweichung[0] << endl;
    imshow("Lineare Skalierung", ls_bild);
    waitKey(0);
    
    
    // b) Gamma-Transformation
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
    
    
    return 0;
}

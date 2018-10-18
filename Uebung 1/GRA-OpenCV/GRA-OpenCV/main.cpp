//
//  GRA-OpenCV Template für alle GRA-Übungen
//
//  Created by Tobias Hahnen on 16.10.18.
//  Copyright © 2018 Tobias Hahnen. All rights reserved.
//

// ÜBUNG 1

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    // Setup
    // Warum auch immer kein relativer Pfad geladen werden kann -.-
    Mat bild = imread("/Users/thahnen/GitHub/gra-uebung/Uebung 1/zelle_grau.bmp", 0);
    
    if (!bild.data) {
        cerr << "Bild konnte nicht geladen werden!" << endl;
        return 1;
    }
    
    
    // 1. Aufgabe
    imshow("Uebung 1", bild);
    waitKey(0);
    
    
    // 2. Aufgabe
    cout << "Breite (px): " << bild.cols << endl;
    cout << "Höhe (px): " << bild.rows << endl;
    cout << "Anzahl Kanäle: " << bild.channels() << endl;
    
    
    // 3. Aufgabe
    Scalar durchschnitt, standard_abweichung;
    meanStdDev(bild, durchschnitt, standard_abweichung);
    cout << "Durchschnittsgrauwert: " << durchschnitt[0] << endl;
    cout << "Standardabweichung: " << standard_abweichung[0] << endl;
    
    
    // 4. Aufgabe
    double min, max;
    minMaxLoc(bild, &min, &max);
    cout << "Kleinster Grauwert im Bild: " << min << endl;
    cout << "Grösster Grauwert im Bild: " << max << endl;
    
    
    // 5. Aufgabe
    int anzahl_pixel = 0;
    
    for (int i=0; i<bild.rows; i++) {
        for (int j=0; j<bild.cols; j++) {
            if (bild.at<uchar>(i, j) > durchschnitt[0]) {
                anzahl_pixel++;
                bild.at<uchar>(i, j) = 255;
            }
        }
    }
    
    cout << "Anzahl der Pixel mit größerem Grauwert als Durchschnitt: " << anzahl_pixel << endl;
    imshow("Uebung 1 - Aufgabe 5", bild);
    waitKey(0);
    
    
    // 6. Aufgabe
    // TODO: Kein Plan wie das geht :(
    
    
    return 0;
}

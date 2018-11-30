//
//  GRA-OpenCV Template für alle GRA-Übungen
//
//  Created by Tobias Hahnen on 16.10.18.
//  Copyright © 2018 Tobias Hahnen. All rights reserved.
//

// ÜBUNG 6

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "definitions.h"


using namespace cv;
using namespace std;


int main(int argc, const char * argv[]) {
    // Setup
    // Warum auch immer kein relativer Pfad geladen werden kann -.-
    Mat bild_1 = imread("/Users/thahnen/GitHub/gra-uebung/Uebung 6/binaer1.bmp", 0);
    Mat bild_2 = imread("/Users/thahnen/GitHub/gra-uebung/Uebung 6/binaer2.bmp", 0);
    if (!bild_1.data) {
        cerr << "Bild konnte nicht geladen werden!" << endl;
        return 1;
    }
    if (!bild_2.data) {
        cerr << "Bild konnte nicht geladen werden!" << endl;
        return 1;
    }
    
    
    // Vor Bearbeitung:
    Scalar durchschnitt, standardabweichung;
    meanStdDev(bild_1, durchschnitt, standardabweichung);
    cout << "\nMittlerer Grauwert (Binaerbild 1): " << durchschnitt[0] << endl;
    cout << "Standardabweichung (Binaerbild 1): " << standardabweichung[0] << endl;
    meanStdDev(bild_2, durchschnitt, standardabweichung);
    cout << "\nMittlerer Grauwert (Binaerbild 2): " << durchschnitt[0] << endl;
    cout << "Standardabweichung (Binaerbild 2): " << standardabweichung[0] << endl;
    imshow("Binaerbild 1", bild_1);
    imshow("Binaerbild 2", bild_2);
    waitKey(0);
    
    
    // Nach Kreisen mit Radius 3-11 suchen
    Mat color;
    cvtColor(bild_1, color, CV_GRAY2RGB);
    Mat temp_1, temp_2;
    
    Mat r3_mask(7, 7, CV_8U, Scalar(0));        // kleiner Kreis
    Mat r11_mask(25, 25, CV_8U, Scalar(255));   // grosser Kreis
    circle(r3_mask, Point(3, 3), 3, Scalar(255), -1);
    circle(r11_mask, Point(12, 12), 11, Scalar(0), -1);
    
    erode(bild_1, temp_1, r3_mask);
    bitwise_not(bild_1, bild_1);
    erode(bild_1, temp_2, r11_mask);
    bitwise_and(temp_1, temp_2, temp_1);
    
    for (int i=0; i<bild_1.rows; i++) {
        for (int j=0; j<bild_1.cols; j++) {
            if (temp_1.at<uchar>(i, j) == 255) {
                floodFill(color, Point(j, i), Scalar(0, 0, 255), 0, Scalar(0), Scalar(0), 4);
                floodFill(temp_1, Point(j, i), Scalar(127, 0, 0), 0, Scalar(0), Scalar(0), 4);
            }
        }
    }
    
    imshow("Kreise 3-11 int Rot", color);
    waitKey(0);
    
    
    // Bild füllen mit morphologischem Füllalgorithmus
    Mat n_bild = bild_2.clone();
    Mat k_bild, temp_3;
    Mat struct_element = getStructuringElement(MORPH_CROSS, Size(3, 3));
    bitwise_not(bild_2, k_bild);                // Invertiertes Bild erzeugen
    n_bild = Scalar(0);
    n_bild.at<uchar>(n_bild.rows/2, n_bild.cols/2) = 255;
    
    int alt;
    do {
        alt = countNonZero(n_bild);             // ermitteln gesetzte Pixel vor Operation
        dilate(n_bild, temp_3, struct_element); // Durchführung Dilatation
        bitwise_and(temp_3, k_bild, n_bild);    // Zum Einschränken der Füllung auf Objekt
    } while (alt != countNonZero(n_bild));
    bitwise_or(bild_2, n_bild, n_bild);
    
    imshow("Ergebnis Fuellung", n_bild);
    waitKey(0);
    
    
    return 0;
}

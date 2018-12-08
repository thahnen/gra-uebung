//
//  GRA-OpenCV Template für alle GRA-Übungen
//
//  Created by Tobias Hahnen on 16.10.18.
//  Copyright © 2018 Tobias Hahnen. All rights reserved.
//

// ÜBUNG 8

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
    Mat bild = imread("/Users/thahnen/GitHub/gra-uebung/Uebung 8/blumen.bmp", 0);
    Mat bild_template = imread("/Users/thahnen/GitHub/gra-uebung/Uebung 8/blumen_template.bmp", 0);
    if (!bild.data) {
        cerr << "Bild konnte nicht geladen werden!" << endl;
        return 1;
    }
    if (!bild_template.data) {
        cerr << "Bild konnte nicht geladen werden!" << endl;
        return 1;
    }
    
    
    // Vor Bearbeitung:
    Scalar durchschnitt, standardabweichung;
    meanStdDev(bild, durchschnitt, standardabweichung);
    cout << "\nMittlerer Grauwert (Blumenbild): " << durchschnitt[0] << endl;
    cout << "Standardabweichung (Blumenbild): " << standardabweichung[0] << endl;
    imshow("Blumenbild", bild);
    imshow("Histogramm: Blumenbild", histogramm(bild));
    imshow("Blumen-Template", bild_template);
    imshow("Histogramm: Blumen-Template", histogramm(bild_template));
    waitKey(0);
    
    
    // Umwandeln des Blumenbilds in eine komplexe Zahl
    Mat real_img[] = { Mat_<float>(bild), Mat::zeros(bild.size(), CV_32F) };
    Mat complex_img, complex_temp;
    Mat ergebnis(bild.rows, bild.cols, CV_32F, Scalar(0));
    
    merge(real_img, 2, complex_img);
    dft(complex_img, complex_img);
    real_img[0] = Scalar(0);
    
    for (int i=0; i<bild_template.rows; i++) {
        for (int j=0; j<bild_template.cols; j++) {
            real_img[0].at<float>(i, j) = (float)bild_template.at<uchar>(i, j);
        }
    }
    
    merge(real_img, 2, complex_temp);
    dft(complex_temp, complex_temp);
    // Multiplikation Bild-FFT mit konjungiert komplexer Template-FFT
    mulSpectrums(complex_img, complex_temp, complex_img, DFT_ROWS, true);
    idft(complex_img, complex_img, DFT_SCALE);
    split(complex_img, real_img);
    normalize(real_img[0], real_img[0], 0, 1, CV_MINMAX);
    
    imshow("1. Ergebnis", real_img[0]);
    waitKey(0);
    
    for (int i=0; i<bild.rows-bild_template.rows-1; i++) {
        for (int j=0; j<bild.cols-bild_template.cols-1; j++) {
            for (int k=0; k<bild_template.rows; k++) {
                for (int l=0; l<bild_template.cols; l++) {
                    ergebnis.at<float>(i, j) += (float)bild.at<uchar>(i+k, j+l) * bild_template.at<uchar>(k, l);
                }
            }
        }
    }
    normalize(ergebnis, bild, 0, 1, CV_MINMAX);
    
    imshow("2. Ergebnis", ergebnis);
    waitKey(0);
    
    
    return 0;
}

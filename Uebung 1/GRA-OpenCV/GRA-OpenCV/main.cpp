//
//  GRA-OpenCV Template für alle GRA-Übungen
//
//  Created by Tobias Hahnen on 16.10.18.
//  Copyright © 2018 Tobias Hahnen. All rights reserved.
//

// ÜBUNG 1

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

Mat histogramm(Mat &bild) {
    int hist_w = 256;
    int hist_h = 450;
    Mat hist_bild(450, 256, CV_8UC3, Scalar(0, 0, 0));
    Mat hist;
    float range[] = {0, 256};
    const float* hist_range = { range };
    calcHist(&bild, 1, 0, Mat(), hist, 1, &hist_w, &hist_range, true, false);
    normalize(hist, hist, 0, hist_bild.rows, NORM_MINMAX, -1, Mat());
    for (int i=0; i<hist_w; i++) {
        line(hist_bild, Point(i, hist_h-cvRound(hist.at<float>(i))), Point(i, hist_h), Scalar(255, 255, 255));
    }
    return hist_bild;
}

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
    imshow("Hist: Normales Bild", histogramm(bild));
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
    Mat n_bild = bild > durchschnitt[0];
    compare(bild, durchschnitt[0], n_bild, CMP_GT);
    
    cout << "Anzahl der Pixel mit größerem Grauwert als Durchschnitt: " << countNonZero(n_bild) << endl;
    
    Mat max_bild;
    cv::max(bild, n_bild, max_bild);
    imshow("Uebung 1 - Aufgabe 5", max_bild);
    imshow("Hist: Größer als Durchschnitt", histogramm(max_bild));
    waitKey(0);
    
    
    // 6. Aufgabe
    Mat farb_bild;
    Mat bild_farben[] = {Mat_<uchar>(bild),Mat_<uchar>(bild),Mat_<uchar>(max_bild)};
    merge(bild_farben, 3, farb_bild);
    
    imshow("Uebung 1 - Aufgabe 6", farb_bild);
    // Das klappt irgendwie nicht, ggf. wegen des Farbbilds?
    //hist_bild = Scalar(0, 0, 0);
    //histogramm(farb_bild, hist_bild, hist_w, hist_h, Scalar(255, 255, 255));
    //imshow("Hist: Farbbild", hist_bild);
    waitKey(0);
    
    return 0;
}

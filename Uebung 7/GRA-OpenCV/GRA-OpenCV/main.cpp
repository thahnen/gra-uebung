//
//  GRA-OpenCV Template für alle GRA-Übungen
//
//  Created by Tobias Hahnen on 16.10.18.
//  Copyright © 2018 Tobias Hahnen. All rights reserved.
//

// ÜBUNG 7

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


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
    Mat bild = imread("/Users/thahnen/GitHub/gra-uebung/Uebung 7/blumen.bmp", 0);
    
    if (!bild.data) {
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
    waitKey(0);
    
    
    return 0;
}

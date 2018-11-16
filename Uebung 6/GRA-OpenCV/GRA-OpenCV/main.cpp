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


using namespace cv;
using namespace std;


void histogramm(Mat &bild, Mat &hist_bild, int hist_w, int hist_h) {
    Mat hist;
    hist_bild = Scalar(0, 0, 0);
    int hist_size = 256;
    float range[] = {0, 256};
    const float* hist_range = { range };
    calcHist(&bild, 1, 0, Mat(), hist, 1, &hist_size, &hist_range, true, false);
    int bin_w = (int)((double)hist_w/hist_size);
    normalize(hist, hist, 0, hist_bild.rows, NORM_MINMAX, -1, Mat());
    for (int i=0; i<hist_size; i++) {
        line(hist_bild, Point(bin_w*(i), hist_h-cvRound(hist.at<float>(i))), Point(bin_w*(i), hist_h), Scalar(255, 255, 255));
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
    Mat bild_1 = imread("/Users/thahnen/GitHub/gra-uebung/Uebung 6/binaer1.bmp", 0);
    Mat bild_2 = imread("/Users/thahnen/GitHub/gra-uebung/Uebung 6/binaer2.bmp", 0);
    int hist_w = 256;
    int hist_h = 450;
    Mat hist_bild(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
    
    if (!bild_1.data) {
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
    
    
    // Nach Kreisen mit Radius 3-11 (Durchmesser 9-25) suchen (funkt nicht ganz)
    Mat suche = bild_1.clone();
    Mat temp = suche.clone();
    Mat r3_mask = Mat::zeros(Size(9, 9), CV_8UC1);
    Mat r11_mask = Mat::zeros(Size(25, 25), CV_8UC1);
    circle(r3_mask, Point(4, 4), 3, Scalar(255, 0, 0), -1);
    circle(r11_mask, Point(12, 12), 11, Scalar(0, 255, 0), -1);
    erode(bild_1, temp, r3_mask);
    bitwise_not(temp, temp);
    erode(temp, suche, r11_mask);
    bitwise_not(suche, suche);
    
    imshow("Kreise zwischen 3-11", suche);
    waitKey(0);
    
    
    // Bild füllen mit morphologischem Füllalgorithmus
    
    
    return 0;
}

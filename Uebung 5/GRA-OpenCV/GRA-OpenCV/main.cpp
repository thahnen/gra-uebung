//
//  GRA-OpenCV Template für alle GRA-Übungen
//
//  Created by Tobias Hahnen on 16.10.18.
//  Copyright © 2018 Tobias Hahnen. All rights reserved.
//

// ÜBUNG 5

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
    Mat bild = imread("/Users/thahnen/GitHub/gra-uebung/Uebung 5/schrift.bmp", 0);
    int hist_w = 256;
    int hist_h = 450;
    Mat hist_bild(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
    
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
    histogramm(bild, hist_bild, hist_w, hist_h);
    imshow("Hist: Normales Bild", hist_bild);
    waitKey(0);
    
    
    return 0;
}

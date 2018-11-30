//
//  definitions.h
//  GRA-OpenCV
//
//  Created by Tobias Hahnen on 30.11.18.
//  Copyright © 2018 Tobias Hahnen. All rights reserved.
//

#ifndef definitions_h
#define definitions_h


#include <opencv2/core/core.hpp>


using namespace cv;


// Funktion um Histogramm eines Bildes zu erlangen
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

// Funktion um Grauwerte zu skalieren
void lineare_skalierung(Mat &bild, Mat &n_bild) {
    double minVal, maxVal;
    minMaxLoc(bild, &minVal, &maxVal);
    convertScaleAbs(bild, n_bild, 255./(maxVal-minVal), -minVal*255./(maxVal-minVal));
}

// Funktion um Filter auf Bild anzuwenden
void filter(Mat &bild, Mat &n_bild, Mat mask) {
    double s, su = sum(mask).val[0];
    for (int j=mask.rows/2; j<bild.rows-mask.rows/2; j++) {
        for (int i=mask.cols/2; i<bild.cols-mask.cols/2; i++) {
            s = 0;
            for (int k=-mask.rows/2; k<=mask.rows/2; k++) {
                for (int l=-mask.cols/2; l<= mask.cols/2; l++) {
                    s += (int)bild.at<uchar>(j+k, i+l)*mask.at<float>(k+ mask.rows/2, l+ mask.cols/2);
                }
            }
            n_bild.at<uchar>(j,i) = s/su;
        }
    }
}

// Funktion um Strukturelement im Bild zu füllen
void fuellen(Mat &bild, Mat &n_bild ){
    Mat kimg, temp;
    Mat element = getStructuringElement(MORPH_CROSS, Size(3,3));
    bitwise_not(bild, kimg);
    n_bild = Scalar(0);
    n_bild.at<uchar>(n_bild.rows/2, n_bild.cols/2) = 255;
    int alt;
    do {
        alt = countNonZero(n_bild);
        dilate(n_bild, temp, element);
        bitwise_and(temp, kimg, n_bild);
    } while (alt != countNonZero(n_bild));
    bitwise_or(bild, n_bild, n_bild);
}

// Funktion um Frequenzraumfilter auf Bild anzuwenden (Siehe Übung 7)
Mat Frequenzraumfilter(const Mat &bild, bool tiefpass, bool gauss) {
    Mat real_bild[] = { Mat_<float>(bild), Mat::zeros(bild.size(), CV_32F) }; // Umwandeln in Komplexe Zahlen mit Realteil = Bild / Imaginaerteil = 0
    Mat complex_bild;
    merge(real_bild, 2, complex_bild);
    dft(complex_bild, complex_bild);                                        // Fourier-Transformation
    
    int cx = complex_bild.cols / 2;
    int cy = complex_bild.rows / 2;
    Mat tmp;
    Mat q0(complex_bild, Rect(0, 0, cx, cy));
    Mat q1(complex_bild, Rect(cx, 0, cx, cy));
    Mat q2(complex_bild, Rect(0, cy, cx, cy));
    Mat q3(complex_bild, Rect(cx, cy, cx, cy));
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);
    
    Mat complexfilter;
    if (!gauss) {
        complexfilter = Mat::zeros(bild.size(), CV_32FC2);
        if (tiefpass) {
            complexfilter = Scalar(0, 0);
            circle(complexfilter, Point(256, 256), 20, Scalar(1, 1), -1);
        } else {
            complexfilter = Scalar(1, 1);
            circle(complexfilter, Point(256, 256), 20, Scalar(0, 0), -1);
        }
    } else {
        Mat filter_r = getGaussianKernel(512, 20.0, CV_32F);
        Mat filter_l;
        transpose(filter_r, filter_l);
        Mat filter = filter_r * filter_l;
        if (!tiefpass) {
            double minVal, maxVal;
            minMaxLoc(filter, &minVal, &maxVal);
            filter = maxVal - filter;
        }
        Mat comp_imag[] = { Mat_<float>(filter),Mat_<float>(filter) };
        merge(comp_imag, 2, complexfilter);
    }
    
    mulSpectrums(complex_bild, complexfilter, complex_bild, DFT_ROWS);      // Filterung mit Maske * Fouriertransformierter
    
    int cxx = complex_bild.cols / 2;
    int cyy = complex_bild.rows / 2;
    Mat tmpp;
    Mat q00(complex_bild, Rect(0, 0, cxx, cyy));
    Mat q11(complex_bild, Rect(cxx , 0, cxx, cyy));
    Mat q22(complex_bild, Rect(0, cyy, cxx, cyy));
    Mat q33(complex_bild, Rect(cxx, cyy, cxx, cyy));
    q00.copyTo(tmpp);
    q33.copyTo(q00);
    tmpp.copyTo(q33);
    q11.copyTo(tmpp);
    q22.copyTo(q11);
    tmpp.copyTo(q22);
    
    idft(complex_bild, complex_bild);                                       // inverse Fourier-Transformation
    split(complex_bild, real_bild);
    normalize(real_bild[0], real_bild[0], 0, 1, CV_MINMAX);
    return real_bild[0];
}


#endif /* definitions_h */

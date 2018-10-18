//
//  main.cpp
//  GRA-OpenCV
//
//  Created by Tobias Hahnen on 16.10.18.
//  Copyright © 2018 Tobias Hahnen. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    // Warum auch immer kein relativer Pfad geladen werden kann -.-
    Mat bild = imread("/Users/thahnen/GitHub/gra-uebung/Uebung 1/zelle_grau.bmp", 0);
    
    if (!bild.data) {
        cerr << "Bild konnte nicht geladen werden!" << endl;
        return 1;
    }
    
    imshow("Test", bild);
    waitKey(0);
    
    for (int i=0; i<bild.rows; i++) {
        for (int j=0; j<bild.cols; j++) {
            bild.at<uchar>(i, j) = 255 - bild.at<uchar>(i, j);
        }
    }
    
    imshow("Test", bild);
    waitKey(0);
    
    return 0;
}

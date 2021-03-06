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
#include "definitions.h"


using namespace cv;
using namespace std;


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
    
    
    // Frequenzraumfilter mit Tiefpass und nicht Gauss
    imshow("Ergebnis idealer Tiefpass", Frequenzraumfilter(bild, true, false));
    waitKey(0);
    
    
    // Frequenzraumfilter mit Tiefpass und Gauss
    imshow("Ergebnis Gausstiefpass", Frequenzraumfilter(bild, true, true));
    waitKey(0);
    
    
    // Frequenzraumfilter mit Hochpass und nicht Gauss
    imshow("Ergebnis idealer Hochpass", Frequenzraumfilter(bild, false, false));
    waitKey(0);
    
    
    // Frequenzraumfilter mit Hochpass und Gauss
    imshow("Ergebnis Gausshochpass", Frequenzraumfilter(bild, false, true));
    waitKey(0);
    
    
    return 0;
}

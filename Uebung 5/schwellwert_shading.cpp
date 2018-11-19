#define _USE_MATH_DEFINES
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <cmath>

using namespace std;


int main(int argc, char *argv[])
{
	//Einlesen des Bildes
	cv::Mat img = cv::imread("schrift.bmp", 0);
	cv::imshow("Original", img);
	cv::Scalar s = cv::mean(img);
	cv::Mat binimg, med, diff, bin;
	cv::threshold(img, binimg, s.val[0], 255, CV_THRESH_BINARY);
	cv::imshow("Binär", binimg);
	cv::medianBlur(img, med, 21);
	cv::subtract(med, img, diff, cv::noArray());
	cv::threshold(diff, bin, 15, 255, CV_THRESH_BINARY);
	cv::imshow("Binär mit Helligkeitskorrektur", bin);
	cv::Mat labels, stats, centroids, col;
	int nLabels = cv::connectedComponentsWithStats(bin, labels, stats, centroids);
	cv::cvtColor(img, col, CV_GRAY2BGR);
	std::vector<cv::Vec3b> colors(nLabels);
	colors[0] = cv::Vec3b(0, 0, 0);
	for (int i = 1; i < stats.rows; i++)
	{
		int x = stats.at<int>(cv::Point(0, i));
		int y = stats.at<int>(cv::Point(1, i));
		int w = stats.at<int>(cv::Point(2, i));
		int h = stats.at<int>(cv::Point(3, i));
		cv::Scalar color(255, 0, 0);
		cv::Rect rect(x, y, w, h);
		cv::rectangle(col, rect, color);
		colors[i] = cv::Vec3b((rand() & 255), (rand() & 255), (rand() & 255));
	}

	cv::imshow("Segmentierte Regionengrenzen", col);
	col = cv::Vec3b(0, 0, 0);
	for (int y = 0; y < col.rows; ++y)
		for (int x = 0; x < col.cols; ++x)
		{
			col.at<cv::Vec3b>(y, x) = colors[labels.at<int>(y, x)];
		}
   cv::imshow("Segmentierte Objekte", col);
   cv::waitKey(0);
}
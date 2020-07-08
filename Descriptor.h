#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include "Moravec.h"

using namespace std;
using namespace cv;

class HOG_DATA
{
public:
	vector<double> HOG;
	cv::Point pt;
	HOG_DATA(vector<double> HOG, cv::Point pt) :
		HOG(std::move(HOG)), pt(pt)
	{
	}
};

class HOG
{
public:
	vector<HOG_DATA> HOG_Algorithm(const Mat &image, Moravec &moravec);
	vector<double> Stack_Histogram(const Mat &magnitude, const Mat &angle);
};
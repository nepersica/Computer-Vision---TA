#pragma once
#include <opencv2/opencv.hpp>

class Moravec
{
private:
	cv::Mat image;
	const int threshold = 35000;
	float **confidence;

public:
	std::vector<cv::Point> keyPointVec;

	Moravec(const cv::Mat &image);
	void CreateConfidence();
	void FindKeyPoint();
	cv::Mat DrawKeyPoint();

};
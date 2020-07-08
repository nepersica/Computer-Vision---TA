#pragma once
#include "opencv2/opencv.hpp"

class SobelX
{
private:
	cv::Mat sobelX;

public:
	void Set_sobelX(cv::Mat &sobelX)
	{
		this->sobelX = sobelX.clone();
	}
	const cv::Mat Get_sobelX() const { return sobelX; }
	
};

class SobelY
{
private:
	cv::Mat sobelY;

public:
	void Set_sobelX(cv::Mat &sobelY)
	{
		this->sobelY = sobelY.clone();
	}
	const cv::Mat Get_sobelY() const { return sobelY; }

};

class SobelFilter
{
public:
	void MakeSobelFilter(const cv::Mat &input_img, SobelX &s_X, SobelY &s_Y);
	double Normalize(double d);
};
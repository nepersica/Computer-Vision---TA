#pragma once
#include <opencv2/opencv.hpp>

class Image1
{
private:
	cv::Mat image1;
	cv::Mat color_img1;

public:
	void Set_Image1(cv::Mat &image1)
	{
		this->color_img1 = image1.clone();
		cv::cvtColor(color_img1, this->image1, CV_RGB2GRAY);
	}
	const cv::Mat Get_Image1() const { return image1; }
	const cv::Mat Get_ColorImage1() const { return color_img1; }
};

class Image2
{
private:
	cv::Mat image2;
	cv::Mat color_img2;

public:
	void Set_Image2(cv::Mat &image2)
	{
		this->color_img2 = image2.clone();
		cv::cvtColor(color_img2, this->image2, CV_RGB2GRAY);
	}
	const cv::Mat Get_Image2() const { return image2; }
	const cv::Mat Get_ColorImage2() const { return color_img2; }
};
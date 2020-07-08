#pragma once
#include <opencv2/opencv.hpp>
#include "Matching.h"
#include "Image.h"
#include <vector>


class Correspond_pt
{
private:
	cv::Point img1_pt;	cv::Point img2_pt;
public:
	Correspond_pt() { };
	Correspond_pt(cv::Point img1_pt, cv::Point img2_pt)
	{
		this->img1_pt = img1_pt;
		this->img2_pt = img2_pt;
	}

	const cv::Point Get_Position1() const
	{
		return img1_pt;
	}

	const cv::Point Get_Position2() const
	{
		return img2_pt;
	}
};


class Ransac
{
private:
public:
	void Get_RotationMat(Image1 &image1, Image2 &image2, const vector<Euclidean_Data> &data);
	cv::Mat Calculate_MatrixT(vector<Correspond_pt> extract_points);
	double Get_Error(cv::Mat &T, Euclidean_Data pts);
	void Attach(const cv::Mat &image1, const cv::Mat &image2, cv::Mat &T);
};
#pragma once
#include <opencv2/opencv.hpp>
#include "Descriptor.h"
#include "Moravec.h"

class Euclidean_Data
{
private:
	vector<Euclidean_Data> matching_data;
	cv::Point img1_px;	cv::Point img2_px;

public:
	Euclidean_Data() {};
	Euclidean_Data(cv::Point img1_px, cv::Point img2_px)
	{
		this->img1_px = img1_px;
		this->img2_px = img2_px;
	}


	void Set_distanceV(vector<Euclidean_Data> vector)
	{
		this->matching_data = vector;
	}

	vector<Euclidean_Data> Get_distanceV() { return matching_data; }

	const cv::Point Get_Position1() const
	{
		return img1_px;
	}

	const cv::Point Get_Position2() const
	{
		return img2_px;
	}

	cv::Point Get_Position1(vector<Euclidean_Data> vector, int idx)
	{
		return vector.at(idx).img1_px;
	}

	cv::Point Get_Position2(vector<Euclidean_Data> vector, int idx)
	{
		return vector.at(idx).img2_px;
	}
};


class Euclidean
{
private:
	vector<Euclidean_Data> euclideanVec;

public:
	void Extract_MinDistance(const vector<HOG_DATA> &img_HOG1, const vector<HOG_DATA> &img_HOG2);
	double Calculate_distance(const vector<double> &hist1, const vector<double> &hist2);
	void Matching(const Mat &image1, const Mat &image2);
	std::vector<Euclidean_Data> Get_euclideanVec()
	{
		return euclideanVec;
	}


}; 

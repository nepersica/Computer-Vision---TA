#pragma once
#include "opencv2\opencv.hpp"
#include <cmath>

class CGeometry
{
private:
	const double PI;
	void matmul(float homoMatrix[3][3]);
	void matmul(float homoCoord[1][3], float outputCoord[1][3]);
	float hmat[3][3]; // 동차행렬

	bool initMat;
	inline double rad(const int degree)
	{
		return degree * (PI / 180.);
	}

public:
	CGeometry(): PI(acos(-1))
	{
		initMat = false;
	}
	void fwmap(cv::Mat& src, cv::Mat& dst);
	void bwmap(cv::Mat& src, cv::Mat& dst);
	void move(const int y, const int x);
	void rotate(const int degree);
	void irotate(const int degree);

	void reset() { initMat = false; }
};

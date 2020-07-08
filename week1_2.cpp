#include <opencv2/opencv.hpp>
#include "SobelFilter.h"
#include "EdgeStrength.h"


int main()
{
	cv::Mat input_img = cv::imread("Lenna.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	
	// ���� 1
	SobelX s_X; SobelY s_Y;
	SobelFilter sobel;
	sobel.MakeSobelFilter(input_img, s_X, s_Y);

	// ���� 2
	EdgeStrength edge_strength;
	edge_strength.GetStrength(input_img.rows, input_img.cols, s_X.Get_sobelX(), s_Y.Get_sobelY());
}


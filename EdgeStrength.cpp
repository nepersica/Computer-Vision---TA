#include "EdgeStrength.h"
#include <cmath>

void EdgeStrength::GetStrength(const int row, const int col, const cv::Mat &sobelX, const cv::Mat &SobelY)
{
	cv::Mat edgeStrength = cv::Mat::zeros(row, col, CV_8UC1);

	// ���� 3.6�� �����Ͽ� ���� ������ ���Ͻÿ�.
	for (int y = 1; y < col-1; y++)
	{
		for (int x = 1; x < row-1; x++)
		{
			edgeStrength.at<uchar>(y, x) = sqrt(pow(sobelX.at<uchar>(y, x), 2) + pow(SobelY.at<uchar>(y, x), 2));
		}
	}
	

	cv::imshow("Edge Strength", edgeStrength);
	cv::waitKey(0);
}
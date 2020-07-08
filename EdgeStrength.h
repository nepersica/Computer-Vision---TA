#include <opencv2/opencv.hpp>

class EdgeStrength
{
public :
	void GetStrength(const int row, const int col, const cv::Mat &sobelX, const cv::Mat &SobelY);
};
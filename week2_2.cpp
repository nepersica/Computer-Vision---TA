#include <opencv2/opencv.hpp>
#include "Image.h"
#include "Moravec.h"

int main()
{
	Image1 image1;	Image2 image2;
	cv::Mat img;

	img = cv::imread("¼Ò³à½Ã´ë 1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	image1.Set_Image1(img);
	img = cv::imread("¼Ò³à½Ã´ë 2.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	image2.Set_Image2(img);

	Moravec moravec1(image1.Get_Image1());
	moravec1.CreateConfidence();
	moravec1.FindKeyPoint();
	cv::Mat result1 = moravec1.DrawKeyPoint();

	Moravec moravec2(image2.Get_Image2());
	moravec2.CreateConfidence();
	moravec2.FindKeyPoint();
	cv::Mat result2 = moravec2.DrawKeyPoint();

	cv::imshow("image1", result1);
	cv::imshow("image2", result2);
	cv::waitKey(0);
}
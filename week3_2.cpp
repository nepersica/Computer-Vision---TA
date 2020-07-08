#include <opencv2/opencv.hpp>
#include "Image.h"
#include "Moravec.h"
#include "Descriptor.h"
#include "Matching.h"
#include "Ransac.h"

int main()
{
	Image1 image1;	Image2 image2;
	cv::Mat img;

	img = cv::imread("¼Ò³à½Ã´ë 1.jpg");
	image1.Set_Image1(img);
	img = cv::imread("¼Ò³à½Ã´ë 2.jpg");
	image2.Set_Image2(img);
	
	Moravec moravec1(image1.Get_Image1());
	moravec1.CreateConfidence();
	moravec1.FindKeyPoint();
	
	Moravec moravec2(image2.Get_Image2());
	moravec2.CreateConfidence();
	moravec2.FindKeyPoint();

	HOG hog;
	vector<HOG_DATA> hog1_img = hog.HOG_Algorithm(image1.Get_Image1(), moravec1);
	vector<HOG_DATA> hog2_img = hog.HOG_Algorithm(image2.Get_Image2(), moravec2);

	Euclidean euclidean;	Euclidean_Data e_data;
	euclidean.Extract_MinDistance(hog1_img, hog2_img);
	euclidean.Matching(image1.Get_Image1(), image2.Get_Image2());

	Ransac ransac;
	ransac.Get_RotationMat(image1, image2, euclidean.Get_euclideanVec());
}
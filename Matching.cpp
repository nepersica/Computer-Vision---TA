#include "Matching.h"
#include <vector>


void Euclidean::Extract_MinDistance(const vector<HOG_DATA>& img_HOG1, const vector<HOG_DATA>& img_HOG2)
{
	vector<Euclidean_Data> vector;
	double threshold = 900;

	for (auto h1 : img_HOG1)
	{
		double min_distance = DBL_MAX;
		cv::Point pt;
		for (auto h2 : img_HOG2)
		{
			double distance = Calculate_distance(h1.HOG, h2.HOG);

			if (min_distance > distance)
			{
				min_distance = distance;
				pt = h2.pt;
			}
		}

		if (threshold > min_distance)
		{
			Euclidean_Data data{ h1.pt, pt };
			vector.push_back(data);
		}
	}

	euclideanVec.assign(vector.begin(), vector.end());
}

double Euclidean::Calculate_distance(const vector<double> &hist1, const vector<double> &hist2)
{

	double result = 0;
	for (int i = 0; i < hist1.size(); i++)
	{
		double hist1_bin_value = hist1.at(i);
		double hist2_bin_value = hist2.at(i);

		result += sqrt(pow((hist1_bin_value - hist2_bin_value), 2));
	}

	return result;
}

void Euclidean::Matching(const Mat &image1, const Mat &image2)
{

	Mat result;
	hconcat(image1, image2, result);

	cvtColor(result, result, CV_GRAY2RGB);

	for (auto v : euclideanVec)
	{
		cv::Point img1_px = v.Get_Position1();
		cv::Point img2_px = v.Get_Position2();

		line(result, Point(img1_px.x, img1_px.y), Point(img2_px.x + image1.cols, img2_px.y), Scalar(0, 0, 255));
	}

	/*imshow("Mathcing Points", result);
	waitKey();*/
}
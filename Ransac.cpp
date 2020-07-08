#include "Ransac.h"
#include <random>

void Ransac::Get_RotationMat(Image1 &image1, Image2 &image2, const vector<Euclidean_Data> &data)
{
	Euclidean_Data e_data;

	random_device _num;		mt19937_64 NUM(_num());
	uniform_real_distribution<> PICK_NUM_RANDOMLY(0, data.size());

	cv::Mat best_T;
	double min_error = DBL_MAX;
	
	// ���� p.325 �˰��� 7-9
	for (int i = 0; i < 1000; i++)
	{
		std::vector<Correspond_pt> extract_pt;
		std::vector<int> ranVec;
		std::vector<Correspond_pt> inlier;

		int count = 0;
		while (count != 3)		// line 3
		{
			int idx = PICK_NUM_RANDOMLY(NUM);
			if (find(ranVec.begin(), ranVec.end(), idx) == ranVec.end())	// �����ϰ� �̾Ƴ� Ư¡���� �ε����� �����ϴ��� Ȯ���ϴ� ���ǹ�
			{
				// �ε����� �������� �ʴ´ٸ� ranVec�� �ش� idx�� �ְ� �ش� points�� extract_pt�� �����ÿ�.
				// Hint1 : Ransac ��� ������ �����Ͽ� Correspond_pt Ŭ������ ��ü�� ����ÿ�.
				//        Correspond_pt points { image1�� point, image2�� point};
				// Hint2 : ��Ī�� point���� ����ִ� ����� data���� Point 1(�̹��� 1�� Point)�� �������� ��� 
				//		  data.at(�ε���).GetPostion1();
				

				count++;
			}
		}

		cv::Mat T = Calculate_MatrixT(extract_pt);	// line 4

		inlier.assign(extract_pt.begin(), extract_pt.end()); // line 5

		for (int i = 0; i < data.size(); i++) // line 6
		{
			if (find(ranVec.begin(), ranVec.end(), i) == ranVec.end())	// line 7
			{
				if (Get_Error(T, data.at(i)) < 1.)
				{
					// data�� ��� ���� �̳��� T�� �����ϸ� inliner�� Correspond_pt Ŭ������ ��ü�� ����� �����ÿ�.
					
				}
			}
		}

		if (inlier.size() > data.size() * 0.7)	// line 9
			T = Calculate_MatrixT(inlier);		// line10

		double error_sum = 0;
		for (int i = 0; i < data.size(); i++)
		{
			error_sum += Get_Error(T, data.at(i));
		}
		
		// line 13
		// error_sum�� min_error���� ������ min_error�� �����ϰ�
		// T�� ��ȯ ��� �� ���� ���� T(best_T)�� �����Ͻÿ�.


	}

	cv::Mat _T = cv::Mat::zeros(3, 3, CV_64FC1);
	// Get_Error �Լ� ���� Matrix _T�� ä�� ��ó�� 
	// best_T�� Matrix _T ���� ä��ÿ�.
	

	Attach(image1.Get_ColorImage1(), image2.Get_ColorImage2(), _T);
}

// ���� p.322||�����ڷ� 7�� ��Ī - ���� 7.12
double Ransac::Get_Error(cv::Mat &T, Euclidean_Data pts)
{
	cv::Mat A(1, 3, CV_64FC1);	cv::Mat _B;
	cv::Mat _T = cv::Mat::zeros(3, 3, CV_64FC1);

	// Matrix A�� ä��ÿ�.
	
	
	// Matrix _T�� ä��ÿ�.
	

	// Matrix _B�� ���Ͻÿ�.


	double error;
	error = pow((_B.at<double>(0, 0) - pts.Get_Position2().y), 2) + pow((_B.at<double>(0, 1) - pts.Get_Position2().x), 2);

	return error;
}

// ���� p.322||�����ڷ� 7�� ��Ī - ���� 7.12
cv::Mat Ransac::Calculate_MatrixT(vector<Correspond_pt> extract_points)
{
	cv::Mat A = cv::Mat::zeros(6, 6, CV_64FC1);
	Correspond_pt data;

	// Make A
	for (auto& v : extract_points)
	{
		cv::Point pt = v.Get_Position1();

		int a1 = pt.y;
		int a2 = pt.x;

		// ���糪 �����ڷḦ �����Ͽ� Matrix A�� ä��ÿ�.
		

	}
	
	cv::Mat B = cv::Mat::zeros(6, 1, CV_64FC1);
	// Make B
	for (auto& v : extract_points)
	{
		cv::Point pt1 = v.Get_Position1();
		cv::Point pt2 = v.Get_Position2();

		int a1 = pt1.y;		int a2 = pt1.x;
		int b1 = pt2.y;		int b2 = pt2.x;

		// ���糪 �����ڷḦ �����Ͽ� Matrix B�� ä��ÿ�.

	}

	// Matrix T�� ���ϴ� ������ �ۼ��Ͻÿ�.
	
	return T.clone();
}

void Ransac::Attach(const cv::Mat &image1, const cv::Mat &image2, cv::Mat &T)
{
	cv::Mat InputImage1 = image1.clone();
	cv::Mat InputImage2 = image2.clone();

	cv::Mat result = cv::Mat::zeros(InputImage1.rows+100, 1500, CV_8UC3);

	cv::Mat A(1, 3, CV_64FC1);
	A.at<double>(0, 0) = InputImage2.rows - 1;
	A.at<double>(0, 1) = InputImage2.cols - 1;
	A.at<double>(0, 2) = 1;

	for (int y = 0; y < InputImage1.rows; y++)
	{
		for (int x = 0; x < InputImage1.cols; x++)
		{
			result.at<Vec3b>(y, x) = InputImage1.at<Vec3b>(y, x);
		}
	}

	int result_x = 0;	int result_y = 0;
	int _x = 0;			int _y = 0;
	for (int y = 0; y < InputImage2.rows; y++)
	{
		for (int x = 0; x < InputImage2.cols; x++)
		{
			
			// ���� ��ǥ y, x�� ���� ��� T�� �̿��� ����� Matrix trans�Դϴ�.
			// �̿� ���� �ҽ� �ڵ�� �ۼ��� �ʿ� ������ �ڵ带 ���� �����ϱ� �ٶ��ϴ�.
			Mat A(1, 3, CV_64FC1);
			A.at<double>(0, 0) = y;
			A.at<double>(0, 1) = x;
			A.at<double>(0, 2) = 1;

			Mat trans = A * T.inv();
			_x = trans.at<double>(0, 1);
			_y = trans.at<double>(0, 0);

			if (_y < 0 || _y > result.rows || _x <0 || _x > result.cols)
				continue;

			result.at<Vec3b>(_y, _x) = InputImage2.at<Vec3b>(y, x);
		}
	}

	imshow("Panorama_GG", result(Range(0, _y), Range(0, _x)));
	waitKey();
}
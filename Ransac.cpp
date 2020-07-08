#include "Ransac.h"
#include <random>

void Ransac::Get_RotationMat(Image1 &image1, Image2 &image2, const vector<Euclidean_Data> &data)
{
	Euclidean_Data e_data;

	random_device _num;		mt19937_64 NUM(_num());
	uniform_real_distribution<> PICK_NUM_RANDOMLY(0, data.size());

	cv::Mat best_T;
	double min_error = DBL_MAX;
	
	// 교재 p.325 알고리즘 7-9
	for (int i = 0; i < 1000; i++)
	{
		std::vector<Correspond_pt> extract_pt;
		std::vector<int> ranVec;
		std::vector<Correspond_pt> inlier;

		int count = 0;
		while (count != 3)		// line 3
		{
			int idx = PICK_NUM_RANDOMLY(NUM);
			if (find(ranVec.begin(), ranVec.end(), idx) == ranVec.end())	// 랜덤하게 뽑아낸 특징점의 인덱스가 존재하는지 확인하는 조건문
			{
				// 인덱스가 존재하지 않는다면 ranVec에 해당 idx를 넣고 해당 points를 extract_pt에 넣으시오.
				// Hint1 : Ransac 헤더 파일을 참고하여 Correspond_pt 클래스의 객체를 만드시오.
				//        Correspond_pt points { image1의 point, image2의 point};
				// Hint2 : 매칭된 point들이 들어있는 결과인 data에서 Point 1(이미지 1의 Point)을 가져오는 방법 
				//		  data.at(인덱스).GetPostion1();
				

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
					// data가 허용 오차 이내로 T에 적합하면 inliner에 Correspond_pt 클래스의 객체로 만들어 넣으시오.
					
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
		// error_sum이 min_error보다 작으면 min_error로 갱신하고
		// T를 변환 행렬 중 가장 좋은 T(best_T)로 지정하시오.


	}

	cv::Mat _T = cv::Mat::zeros(3, 3, CV_64FC1);
	// Get_Error 함수 내의 Matrix _T를 채운 것처럼 
	// best_T를 Matrix _T 내에 채우시오.
	

	Attach(image1.Get_ColorImage1(), image2.Get_ColorImage2(), _T);
}

// 교재 p.322||강의자료 7장 매칭 - 수식 7.12
double Ransac::Get_Error(cv::Mat &T, Euclidean_Data pts)
{
	cv::Mat A(1, 3, CV_64FC1);	cv::Mat _B;
	cv::Mat _T = cv::Mat::zeros(3, 3, CV_64FC1);

	// Matrix A를 채우시오.
	
	
	// Matrix _T를 채우시오.
	

	// Matrix _B를 구하시오.


	double error;
	error = pow((_B.at<double>(0, 0) - pts.Get_Position2().y), 2) + pow((_B.at<double>(0, 1) - pts.Get_Position2().x), 2);

	return error;
}

// 교재 p.322||강의자료 7장 매칭 - 수식 7.12
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

		// 교재나 강의자료를 참고하여 Matrix A를 채우시오.
		

	}
	
	cv::Mat B = cv::Mat::zeros(6, 1, CV_64FC1);
	// Make B
	for (auto& v : extract_points)
	{
		cv::Point pt1 = v.Get_Position1();
		cv::Point pt2 = v.Get_Position2();

		int a1 = pt1.y;		int a2 = pt1.x;
		int b1 = pt2.y;		int b2 = pt2.x;

		// 교재나 강의자료를 참고하여 Matrix B를 채우시오.

	}

	// Matrix T를 구하는 수식을 작성하시오.
	
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
			
			// 동차 좌표 y, x와 동차 행렬 T를 이용한 결과인 Matrix trans입니다.
			// 이에 대한 소스 코드는 작성할 필요 없으니 코드를 보고 이해하길 바랍니다.
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
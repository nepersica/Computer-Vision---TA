#include "SobelFilter.h"

void SobelFilter::MakeSobelFilter(const cv::Mat &input_img, SobelX &s_X, SobelY &s_Y)
{
	cv::Mat img = input_img.clone();

	// 소벨 마스크 m_y와 m_x를 2차원 배열로 작성하시오.
	double m_y[3][3] = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1} };
	double m_x[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };

	cv::Mat sobelY = cv::Mat::zeros(img.rows, img.cols, CV_8UC1);
	cv::Mat sobelX = cv::Mat::zeros(img.rows, img.cols, CV_8UC1);

	for (int y = 0; y < img.rows; y++)
	{
		for (int x = 0; x < img.cols; x++)
		{
			// 이미지의 가장자리를 필터 연산에 포함하지 않는 조건문을 작성하시오.
			if (y == 0 || y == img.rows - 1 || x == 0 || x == img.cols - 1)
			{
				sobelX.at<uchar>(y, x) = img.at<uchar>(y, x);
				continue;
			}

			cv::Mat present_windows = cv::Mat::zeros(3, 3, CV_8UC1);
			for (int i = -1; i < 2; i++)
			{
				for (int j = -1; j < 2; j++)
				{
					present_windows.at<uchar>(i + 1, j + 1) = img.at<uchar>(y + i, x + j);
				}
			}

			double d_y = 0; double d_x = 0;

			// 소벨 마스크 m_y에 대하여 계산하시오.
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					d_y += m_y[i][j] * present_windows.at<uchar>(i, j);
				}
			}

			// 소벨 마스크 m_x에 대하여 계산하시오.
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					d_x += m_x[i][j] * present_windows.at<uchar>(i, j);
				}
			}

			
			d_y = Normalize(d_y);
			d_x = Normalize(d_x);

			sobelY.at<uchar>(y, x) = d_y;
			sobelX.at<uchar>(y, x) = d_x;
		}
	}

	// 이 밑의 코드는 수정하지 않아도 됩니다.
	cv::Mat exercise_sobel = sobelX + sobelY;

	s_X.Set_sobelX(sobelX);
	s_Y.Set_sobelX(sobelY);

	cv::imshow("exercise_y", sobelY);
	cv::imshow("exercise_x", sobelX);
	cv::imshow("exercise_sobel", exercise_sobel);
	cv::waitKey(0);
}

double SobelFilter::Normalize(double d)
{
	// 결과 값을 0~255로 정규화하시오.
	if (d > 255)
	{
		d = 255;
	}
	else if (d < 0)
	{
		d = 0;
	}

	return d;
}

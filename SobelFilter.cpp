#include "SobelFilter.h"

void SobelFilter::MakeSobelFilter(const cv::Mat &input_img, SobelX &s_X, SobelY &s_Y)
{
	cv::Mat img = input_img.clone();

	// �Һ� ����ũ m_y�� m_x�� 2���� �迭�� �ۼ��Ͻÿ�.
	double m_y[3][3] = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1} };
	double m_x[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };

	cv::Mat sobelY = cv::Mat::zeros(img.rows, img.cols, CV_8UC1);
	cv::Mat sobelX = cv::Mat::zeros(img.rows, img.cols, CV_8UC1);

	for (int y = 0; y < img.rows; y++)
	{
		for (int x = 0; x < img.cols; x++)
		{
			// �̹����� �����ڸ��� ���� ���꿡 �������� �ʴ� ���ǹ��� �ۼ��Ͻÿ�.
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

			// �Һ� ����ũ m_y�� ���Ͽ� ����Ͻÿ�.
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					d_y += m_y[i][j] * present_windows.at<uchar>(i, j);
				}
			}

			// �Һ� ����ũ m_x�� ���Ͽ� ����Ͻÿ�.
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

	// �� ���� �ڵ�� �������� �ʾƵ� �˴ϴ�.
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
	// ��� ���� 0~255�� ����ȭ�Ͻÿ�.
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

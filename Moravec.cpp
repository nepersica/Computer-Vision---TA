#include "Moravec.h"

Moravec::Moravec(const cv::Mat &image)
{
	this->image = image.clone();

	confidence = new float*[image.rows];
	for (int i = 0; i < image.rows; i++)
	{
		confidence[i] = new float[image.cols];
	}
	for (int i = 0; i < image.rows; i++)
	{
		memset(confidence[i], 0, sizeof(float)*image.cols);
	}
}

void Moravec::CreateConfidence()
{
	for (int h = 2; h < image.rows - 2; ++h)
	{
		for (int w = 2; w < image.cols - 2; ++w)
		{
			// 3x3 그리드의 중점이 (0, 0)이라고 가정.
			// S1 = (-1, 0), S2 = (1, 0), S3 = (0, -1), S4 = (0, 1)
			int s1 = 0;			int s2 = 0;
			int s3 = 0;			int s4 = 0;
			
			// 3x3 그리드
			for (int y = -1; y <= 1; ++y)
			{
				for (int x = -1; x <= 1; ++x)
				{
					// 교재 p.163 / 강의자료 p.9에 있는 예제 4-1을 참고하여 제곱차합을 계산하시오.
					float top = image.at<uchar>((h + y), (w + x)) - image.at<uchar>((h + y - 1), (w + x)); // 상
					float bottom = image.at<uchar>((h + y), (w + x)) - image.at<uchar>((h + y + 1), (w + x)); // 하
					float left = image.at<uchar>((h + y), (w + x)) - image.at<uchar>((h + y), (w + x - 1)); // 좌
					float right = image.at<uchar>((h + y), (w + x)) - image.at<uchar>((h + y), (w + x + 1)); // 우

					s1 += pow(top, 2);
					s2 += pow(bottom, 2);
					s3 += pow(left, 2);
					s4 += pow(right, 2);
				}
			}

			// s1, s2, s3, s4 중 가장 작은 값을 confidence 배열에 추가하시오.
			int c = std::min(std::min(s1, s2), std::min(s3, s4));
			confidence[h][w] = c;
		}
	}
}

void Moravec::FindKeyPoint()
{
	for (int y = 16; y < image.rows - 16; ++y)
	{
		for (int x = 16; x < image.cols - 16; ++x)
		{
			// 임계값보다 큰 값의 좌표를 keyPointVec에 추가하시오.
			if (confidence[y][x] >= threshold)
				keyPointVec.push_back(cv::Point(x, y));
		}
	}

}

cv::Mat Moravec::DrawKeyPoint()
{
	cv::cvtColor(image, image, CV_GRAY2BGR);

	for (int i = 0; i < keyPointVec.size(); i++)
	{
		cv::Point keyPoint = keyPointVec[i];
		cv::circle(image, cv::Point(keyPoint.x, keyPoint.y), 3, cv::Scalar(0, 0, 255));
	}


	return image;
}

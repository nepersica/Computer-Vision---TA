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
			// 3x3 �׸����� ������ (0, 0)�̶�� ����.
			// S1 = (-1, 0), S2 = (1, 0), S3 = (0, -1), S4 = (0, 1)
			int s1 = 0;			int s2 = 0;
			int s3 = 0;			int s4 = 0;
			
			// 3x3 �׸���
			for (int y = -1; y <= 1; ++y)
			{
				for (int x = -1; x <= 1; ++x)
				{
					// ���� p.163 / �����ڷ� p.9�� �ִ� ���� 4-1�� �����Ͽ� ���������� ����Ͻÿ�.
					float top = image.at<uchar>((h + y), (w + x)) - image.at<uchar>((h + y - 1), (w + x)); // ��
					float bottom = image.at<uchar>((h + y), (w + x)) - image.at<uchar>((h + y + 1), (w + x)); // ��
					float left = image.at<uchar>((h + y), (w + x)) - image.at<uchar>((h + y), (w + x - 1)); // ��
					float right = image.at<uchar>((h + y), (w + x)) - image.at<uchar>((h + y), (w + x + 1)); // ��

					s1 += pow(top, 2);
					s2 += pow(bottom, 2);
					s3 += pow(left, 2);
					s4 += pow(right, 2);
				}
			}

			// s1, s2, s3, s4 �� ���� ���� ���� confidence �迭�� �߰��Ͻÿ�.
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
			// �Ӱ谪���� ū ���� ��ǥ�� keyPointVec�� �߰��Ͻÿ�.
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

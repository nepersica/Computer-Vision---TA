#include <opencv2/opencv.hpp>

using namespace cv;

void Read_img(Mat img)
{
	if (img.empty())
	{
		std::cout << "잘못된 파일 이름입니다." << std::endl;
		exit(0);
	}

	imshow("Exercise_1", img);
	waitKey(0);
}

void Histogram(Mat img)
{
	Mat gray_img;
	cvtColor(img, gray_img, COLOR_BGR2GRAY);

	int histogram[256] = { 0 };

	for (int y = 0; y < gray_img.rows; y++)
	{
		for (int x = 0; x < gray_img.cols; x++)
		{
			histogram[gray_img.at<uchar>(y, x)]++;
		}
	}

	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / 256);

	Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(255, 255, 255));

	// 최대 요소 찾기
	int max = histogram[0];
	for (int i = 0; i < 256; i++)
	{
		if (max < histogram[i])
			max = histogram[i];
	}

	// 정규화
	for (int i = 0; i < 255; i++)
		histogram[i] = ((double)histogram[i] / max) * histImage.rows;

	// 히스토그램 그래프 그리기
	for (int i = 0; i < 255; i++)
		line(histImage, Point(bin_w*(i), hist_h), Point(bin_w*(i), hist_h - histogram[i]), Scalar(0, 0, 0), 1, 8, 0);

	namedWindow("Exercise_2-Intensity Histogram", CV_WINDOW_AUTOSIZE);
	imshow("Exercise_2-Intensity Histogram", histImage);

	namedWindow("Exercise_2", CV_WINDOW_AUTOSIZE);
	imshow("Exercise_2", gray_img);
	waitKey(0);

}

int main()
{
	Mat img = imread("Lenna.jpg", cv::IMREAD_COLOR);
	Read_img(img);
	Histogram(img);
}


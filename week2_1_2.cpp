#include "opencv2\opencv.hpp"
#include "Geometry.h"

using namespace cv;
using namespace std;

void LPF(Mat src, Mat dst) {

	double mask[9] = {
		1. / 9, 1. / 9, 1. / 9,
		1. / 9, 1. / 9, 1. / 9,
		1. / 9, 1. / 9, 1. / 9
	};
	for (int h = 1; h < src.rows - 1; h++) {
		for (int w = 1; w < src.cols - 1; w++) {

			double sum = 0;
			int idx = 0;

			for (int x = -1; x <= 1; x++) {
				for (int y = -1; y <= 1; y++) {
					sum += mask[idx] * src.at<uchar>(h + x, w + y);

					idx++;
				}
			}
			dst.at<uchar>(h, w) = cv::saturate_cast<uchar>(sum);
		}
	}
}

int main() {

	Mat src, dst, dst2;

	src = imread("Lenna.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	dst.create(src.size(), CV_8UC1);
	dst2.create(src.size(), CV_8UC1);

	if (src.empty()) {
		cout << "No File..." << endl;
		return -1;
	}

	CGeometry geometry;

	// Rotate
	geometry.move(-(src.rows / 2), -(src.cols / 2));
	geometry.irotate(70);
	geometry.move(src.rows / 2, src.cols / 2);

	geometry.bwmap(src, dst);
	LPF(dst, dst2);

	imshow("Original", src);
	imshow("Result", dst);
	imshow("LPF Result", dst2);
	waitKey(0);

	return 0;
}
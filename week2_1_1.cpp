#include "opencv2\opencv.hpp"
#include "Geometry.h"

using namespace cv;
using namespace std;

int main() {
	Mat src, dst;

	src = imread("Lenna.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	dst.create(src.size(), CV_8UC1);

	if (src.empty()) {
		cout << "No File..." << endl;
		return -1;
	}

	CGeometry geometry;

	// Rotate
	geometry.move(-(src.rows / 2), -(src.cols / 2));
	geometry.rotate(70);
	geometry.move(src.rows / 2, src.cols / 2);

	geometry.fwmap(src, dst);

	imshow("Original", src);
	imshow("Result", dst);
	waitKey(0);

	return 0;
}
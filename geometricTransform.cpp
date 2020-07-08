#include "Geometry.h"

void CGeometry::matmul(float homoMatrix[3][3])
// 3 x 3 행렬 연산
{
	if (!initMat)
	{
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				hmat[i][j] = homoMatrix[i][j];
		initMat = true;
		return;
	}

	float mult[3][3] = { 0., };

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			for (int k = 0; k < 3; ++k)
				mult[i][j] += hmat[i][k] * homoMatrix[k][j];

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			hmat[i][j] = mult[i][j];
}

void CGeometry::matmul(float homoCoord[1][3], float outputCoord[1][3])
// 1 x 3 행렬 연산
{
	for (int i = 0; i < 1; ++i)
		for (int j = 0; j < 3; ++j)
			for (int k = 0; k < 3; ++k)
				outputCoord[i][j] += homoCoord[i][k] * hmat[k][j];
}

void CGeometry::fwmap(cv::Mat& src, cv::Mat& dst)
// 전방 기하 변환
{
	float homoCoord[1][3] = { 0., };
	for (int y = 0; y < src.rows; ++y)
	{
		for (int x = 0; x < src.cols; ++x)
		{
			homoCoord[0][0] = y;
			homoCoord[0][1] = x;
			homoCoord[0][2] = 1;
			float outputCoord[1][3] = { 0., };
			matmul(homoCoord, outputCoord);

			if (outputCoord[0][0] < 0 || outputCoord[0][1] < 0 ||
				outputCoord[0][0] > dst.rows - 1 || outputCoord[0][1] > dst.cols - 1)
				continue;
			

			dst.at<uchar>( round(outputCoord[0][0]), round(outputCoord[0][1]) ) = src.at<uchar>(y, x);
		}
	}
}

void CGeometry::bwmap(cv::Mat& src, cv::Mat& dst)
// 후방 기하 변환
{
	float homoCoord[1][3] = { 0., };
	for (int y = 0; y < src.rows; ++y)
	{
		for (int x = 0; x < src.cols; ++x)
		{
			homoCoord[0][0] = y;
			homoCoord[0][1] = x;
			homoCoord[0][2] = 1;
			float outputCoord[1][3] = { 0., };
			matmul(homoCoord, outputCoord);

			if (outputCoord[0][0] < 0 || outputCoord[0][1] < 0 ||
				outputCoord[0][0] > src.rows - 1 || outputCoord[0][1] > src.cols - 1)
				continue;

			dst.at<uchar>(y, x) = src.at<uchar>(round(outputCoord[0][0]), round(outputCoord[0][1]));
		}
	}
}

void CGeometry::move(const int y, const int x)
// 좌표 이동
{
	float MoveHomoMatrix[3][3];

	MoveHomoMatrix[0][0] = 1;
	MoveHomoMatrix[0][1] = 0;
	MoveHomoMatrix[0][2] = 0;

	MoveHomoMatrix[1][0] = 0;
	MoveHomoMatrix[1][1] = 1;
	MoveHomoMatrix[1][2] = 0;

	MoveHomoMatrix[2][0] = y;
	MoveHomoMatrix[2][1] = x;
	MoveHomoMatrix[2][2] = 1;

	matmul(MoveHomoMatrix);
}

void CGeometry::rotate(const int degree)
// 회전 변환
{
	float RotateHomoMatrix[3][3];
	double radian = rad(degree);
	// 회전에 대한 동차행렬을 완성하세요.
	RotateHomoMatrix[0][0] = cos(radian);
	RotateHomoMatrix[0][1] = -sin(radian);
	RotateHomoMatrix[0][2] = 0;
	
	RotateHomoMatrix[1][0] = sin(radian);
	RotateHomoMatrix[1][1] = cos(radian);
	RotateHomoMatrix[1][2] = 0;
	
	RotateHomoMatrix[2][0] = 0;
	RotateHomoMatrix[2][1] = 0;
	RotateHomoMatrix[2][2] = 1;

	matmul(RotateHomoMatrix);
}

void CGeometry::irotate(const int degree)
// 회전 역변환
{
	float RotateHomoMatrix[3][3];
	double radian = rad(degree);
	// 회전에 대한 동차행렬을 완성하세요.
	RotateHomoMatrix[0][0] = cos(-radian);
	RotateHomoMatrix[0][1] = -sin(-radian);
	RotateHomoMatrix[0][2] = 0;

	RotateHomoMatrix[1][0] = sin(-radian);
	RotateHomoMatrix[1][1] = cos(-radian);
	RotateHomoMatrix[1][2] = 0;

	RotateHomoMatrix[2][0] = 0;
	RotateHomoMatrix[2][1] = 0;
	RotateHomoMatrix[2][2] = 1;

	matmul(RotateHomoMatrix);
}
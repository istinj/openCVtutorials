//! Harris - Shi TomasicCorner detection implementations

#include "iostream"
#include "stdio.h"
#include "stdlib.h"
#include "cmath"

#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

RNG rng(12345);

// Functions
vector<Point> harrisDetector(const Mat& image_, int block_, int sobel_size_, float k_,int tr_ );
vector<Point2f> stDetector(const Mat &image_, int maxCorn_, double quality_, double minD_, int bblock_, const double kk_);

int thres = 80;
Mat src, copy_src, copy_src_2, gray, dst, norm_gray, absNorm_gray;

char src_wind[] = "Source Image";
char wind_1[] = "OpenCV Harris Detector";
char wind_2[] = "OpenCV Shi-Tomasi goodFeaturesToTrack";

int main(int argc, char const *argv[])
{
	//! Load the image
	src = imread(argv[1], CV_LOAD_IMAGE_UNCHANGED);
	copy_src = src;
	copy_src_2 = src;
	namedWindow(src_wind, WINDOW_NORMAL);
	imshow(src_wind, src);
	waitKey(0);

	//! Grayscaled image
	cvtColor(src, gray, COLOR_BGR2GRAY);

	
	std::vector<Point> v;
	int b = 2;
	int s = 3;
	v = harrisDetector(gray, b, s, 0.04f, thres);
	for (int i = 0; i < v.size(); i++)
		circle(copy_src, v[i], 5, Scalar(rng.uniform(0,255), rng.uniform(0,255), rng.uniform(0,255)), 2, 8, 0);
	namedWindow(wind_1, WINDOW_NORMAL);
	imshow(wind_1, copy_src);
	waitKey(0);


	std::vector<Point2f> c;
	c = stDetector(gray, 100, 0.01, 10, 3, 0.04);
	for (int i = 0; i < c.size(); i++)
		circle(copy_src_2, c[i], 5, Scalar(rng.uniform(0,255), rng.uniform(0,255), rng.uniform(0,255)), 2, 8, 0);
	namedWindow(wind_2, WINDOW_NORMAL);
	imshow(wind_2, copy_src_2);
	waitKey(0);

	return 0;
}


//!  ---------------------------------- OpenCV implementation of Harris CD ---------------------------------- //
vector<Point> harrisDetector(const Mat &image_, int block_, int sobel_size_, const float k_, int tr_)
{
	Mat copied_ = image_;
	Mat dest_, norm_, converted;
	std::vector<Point> harris_vector;

	cornerHarris(copied_, dest_, block_, sobel_size_, k_ , BORDER_DEFAULT);
	normalize(dest_, norm_, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
	convertScaleAbs(norm_, converted);

	for (int i = 0; i < norm_.rows; i++)
	{
		for (int j = 0; j < norm_.cols; j++)
		{
			if ((int)norm_.at<float>(i, j) > tr_)
			{
				harris_vector.push_back(Point(j, i));
			}
		}
	}
	printf("size: %d\n", (int)harris_vector.size());

	return harris_vector;

}


//!  ---------------------------------- OpenCV implementation of Shi-Tomasi CD ---------------------------------- //
vector<Point2f> stDetector(const Mat &image_, int maxCorn_, double quality_, double minD_, int bblock_, const double kk_)
{
	Mat copied_ = image_;
	std::vector<Point2f> corners_v;

	if (maxCorn_ < 1) maxCorn_ = 1;

	goodFeaturesToTrack(copied_, corners_v, maxCorn_, 
		quality_, minD_, Mat(), bblock_, false, kk_);

	return corners_v;
}


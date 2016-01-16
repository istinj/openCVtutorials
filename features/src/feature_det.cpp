#include <stdio.h>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

char src_windowname[] = "Source Image";
char windowname_1[] = "No Harris";
char windowname_2[] = "Harris";
RNG rng(12345);

int main(int argc, char const *argv[])
{
	Mat src_image = imread(argv[1], CV_LOAD_IMAGE_UNCHANGED);
	Mat colored = src_image;
	Mat gray;
	Size src_s = src_image.size();
	printf("%d %d\n", src_s.width, src_s.height);
	cvtColor(src_image, gray, COLOR_BGR2GRAY);

	namedWindow(src_windowname, WINDOW_NORMAL);
	imshow(src_windowname, src_image);

	namedWindow(windowname_1, WINDOW_NORMAL);
	namedWindow(windowname_2, WINDOW_NORMAL);

	waitKey(0);

	// cv::GFTTDetector detector = GFTTDetector(10, 0.01, 10, 3, 0, 0.04);
	// detector.detect(_current_gray, keypoints, _mask);

	vector<Point2f> corners;
	int maxCorners = 50;
	double qualityLevel = 0.11;
	double minDistance = 10;
	int blockSize = 3;
	bool useHarrisDetector = false;
	double k = 0.04;
	goodFeaturesToTrack( gray,
	             corners,
	             maxCorners,
	             qualityLevel,
	             minDistance,
	             Mat(),
	             blockSize,
	             useHarrisDetector,
	             k );

	int r = 10;
	for( int i = 0; i < corners.size(); i++ )
	   { circle( colored, corners[i], r, Scalar(rng.uniform(0,255), rng.uniform(0,255),
	            rng.uniform(0,255)), 3 ); }
	imshow(windowname_1, colored);

	waitKey(0);

	goodFeaturesToTrack( gray,
	             corners,
	             maxCorners,
	             qualityLevel,
	             minDistance,
	             Mat(),
	             blockSize,
	             true,
	             k );
	for( int i = 0; i < corners.size(); i++ )
	   { circle( colored, corners[i], r, Scalar(rng.uniform(0,255), rng.uniform(0,255),
	            rng.uniform(0,255)), 3 ); }
	imshow(windowname_2, colored);

	waitKey(0);

	// ------------ My Harris Corner detection ----------//
	// Mat H = Mat::zeros(src_image.rows, src_image.cols, CV_32F);
	// Mat norm_H = Mat::zeros(src_image.rows, src_image.cols, CV_32F);
	// Mat absNorm_H = Mat::zeros(src_image.rows, src_image.cols, CV_32F);
	Mat H, norm_H, absNorm_H;
	// H = Mat::zeros( src_image.size(), CV_32FC1 );

	cornerHarris(gray, H, 2, 3, 0.04, BORDER_DEFAULT);
	imshow(src_windowname, H);
	waitKey(0);
	// normalize and scale the values
	normalize(H, norm_H, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
	imshow(src_windowname, norm_H);
	waitKey(0);
	convertScaleAbs(norm_H, absNorm_H);
	imshow(src_windowname, absNorm_H);
	waitKey(0);

	// Intensity threshold: if int > threshold -> mark the pixel as corner
	int threshold_ = 80;
	vector<Point2f> h_c_vector;
	// cicling for all the pixels
	for (int i = 0; i < src_image.rows; i++)
	{
		for (int j = 0; j < src_image.cols; j++)
		{
			if ((int)norm_H.at<float>(i,j) > (int)threshold_)
			{
				h_c_vector.push_back(Point2f(j,i));
			}
		}
	}
	for (int k = 0; k < h_c_vector.size(); k++)
	{
		circle(absNorm_H, h_c_vector[k], 5, Scalar(0), 1);
	}
	imshow(src_windowname, absNorm_H);
	waitKey(0);
	printf("size: %d\n", (int)h_c_vector.size());






	return 0;
}
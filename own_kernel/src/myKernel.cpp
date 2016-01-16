//! Building my own kernel

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

char src_windowname[] = "Source Image";
char prc_windowname[] = "Filtered image";
char filters_windowname[] = "Current Filter";

Mat create_kernel(int kernel_size, float sigma);


int main(int argc, char const *argv[])
{
	Mat src_image = imread(argv[1], CV_LOAD_IMAGE_UNCHANGED);
	namedWindow(src_windowname, WINDOW_NORMAL);
	imshow(src_windowname, src_image);

	waitKey(0);

	Mat gauss = create_kernel(13, 1.1f);

	// Filtering arguments
	Point anchor_point = Point(-1, -1);
	double delta = 0;
	int ddepth = -1;
	Mat prc_image;

	// Filtering the image
	filter2D(src_image, prc_image, ddepth, gauss, anchor_point, delta, BORDER_DEFAULT);
	namedWindow(prc_windowname, WINDOW_NORMAL);
	imshow(prc_windowname, prc_image);
	waitKey(0);


	// SOBEL FILTERS
	float s_f_data[3][3] = {{-3,-10,-3}, {3, 10, 3}, {0, 0, 0}};
	Mat scharr_hor = Mat(3, 3, CV_32F, s_f_data);
	Mat scharr_ver = scharr_hor.t();

	namedWindow(filters_windowname, WINDOW_NORMAL);
	imshow(filters_windowname, scharr_hor);
	filter2D(src_image, prc_image, ddepth, scharr_hor, anchor_point, delta, BORDER_DEFAULT);
	imshow(prc_windowname, prc_image);
	waitKey(0);

	namedWindow(filters_windowname, WINDOW_NORMAL);
	imshow(filters_windowname, scharr_ver);
	filter2D(src_image, prc_image, ddepth, scharr_ver, anchor_point, delta, BORDER_DEFAULT);
	imshow(prc_windowname, prc_image);
	waitKey(0);

	return 0;
}


Mat create_kernel(int kernel_size, float sigma)
{
	float s_sqr, r, sum, ii, jj;
	int mid_size;
	Mat k = Mat::eye(kernel_size, kernel_size, CV_32F);

	char windowname[] = "Gaussian Filter";
	
	// auto k_matrix_type = Mat::type(k);
	mid_size = (int)kernel_size / 2;
	s_sqr = sigma * sigma;
	sum = 0;

	for (int i = -mid_size; i <= mid_size; i++)
	{
		for (int j = -mid_size; j <= mid_size; j++)
		{
			r = sqrt(i*i + j*j);
			k.at<float>((i + mid_size),(j + mid_size)) = (exp(-(r * r)/(2.0f * s_sqr)))/(3.14 * 2.0f * s_sqr);
			sum += k.at<float>((i + mid_size),(j + mid_size));
		}
	}
	for (int i = -mid_size; i < mid_size; i++)
		for (int j = -mid_size; j < mid_size; j++)
			k.at<float>((i + mid_size),(j + mid_size)) /= sum;

	namedWindow(windowname, WINDOW_NORMAL);
	imshow(windowname, k);
	return k;
}
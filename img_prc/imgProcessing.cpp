//! Some poor-man image processing

#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

char src_window_name[] = "Source image";
char prc_window_name[] = "Processed image";

int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		cout<<"\nError, missing the image"<<endl;
		return -1;
	}
	Mat image = imread(argv[1], CV_LOAD_IMAGE_UNCHANGED);
	Mat f_image;
	namedWindow(src_window_name, WINDOW_NORMAL);
	imshow(src_window_name, image);

	waitKey(0);
	namedWindow(prc_window_name, WINDOW_NORMAL);

	// Normalized Block Filter
	blur(image, f_image, Size(13,13), Point(-1,-1));
	imshow(prc_window_name, f_image);

	waitKey(0);

	// Gaussian filter
	GaussianBlur(image, f_image, Size(13,13), 1.5, 1.5);
	imshow(prc_window_name, f_image);

	waitKey(0);

	return 0;
}
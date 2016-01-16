//! This script loads and shows an image

#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main (int argc, char** argv)
{
	if ( argc != 2 )
	{
		std::cout <<"\nUsage: script_name path_to_the_image" << std::endl;
		return -1;
	}
	char* image_file = argv[1];
	Mat image, g_image;
	image = imread(image_file, CV_LOAD_IMAGE_UNCHANGED);

	if ( image.data == false )
	{
		std::cout <<"\nUsage: script_name path_to_the_image" << std::endl;
		return -1;
	}

	cvtColor(image, g_image, CV_BGR2GRAY);
	namedWindow("Image", WINDOW_NORMAL);
	imshow("Image", image);

	waitKey(0);

	namedWindow("Grayscaled image", WINDOW_NORMAL);
	imshow("Grayscaled image", g_image);

	waitKey(0);

	return 0;
}
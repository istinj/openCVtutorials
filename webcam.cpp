//! This script shows what the webcam sees

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "iostream"
#include "stdio.h"

using namespace std;
using namespace cv;

int main(int argc, char const *argv[])
{
	VideoCapture cap(0);
	if (cap.isOpened())
		return -1;

	Mat edges, frame;
	namedWindow("edges", WINDOW_NORMAL);

	//loop indefinitely
	while(true)
	{
		cap >> frame;
		imshow("Cam", frame);
		if (waitKey(30)>=0) break;
	}
	return 0;
}
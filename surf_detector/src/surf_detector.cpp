//! Features detector and matcher using SURF algorithm

// To decide if a pixel in an image is a SURF keypoint, an approximation of the Hessian
// matrix is built with the partial derivatives of the image intensities within
// a patch around the pixel. The determinant of this matrix is called Hessian and 
// tells you how robust that pixel is as a blob center.

// The minHessian is a threshold to decide from which value you are willing to 
// accept keypoints. In practice, the higher the minHessian, the fewer keypoints 
// you will obtain, but you expect them to be more repetitive 
// (w.r.t. image transformations), and then, more useful. 
// On the other hand, the lower the minHessian, the more keypoints you get, 
// but they may be more noisy.

// In usual images, a value between 400 and 800 works well.

// Note that SurfFeatureDetector does not provide a way to select just a fixed number of 
// keypoints. To do so, you have to set a low minHessian, sort the resulting 
// keypoints by its Hessian value and then remove the least persistent ones.

#include "iostream"
#include "stdio.h"
#include "stdlib.h"
#include "cmath"

#include "opencv2/opencv.hpp"
#include "opencv2/nonfree/features2d.hpp"

using namespace std;
using namespace cv;

RNG rng(12345);

char first_src[] = "First image";
char second_src[] = "Second image";
char match_window[] = "Matches between images";

Mat src_1, src_2, gray_1, gray_2;
std::vector<KeyPoint> keypoints_1, keypoints_2, sort_keypoints_1, sort_keypoints_2;
std::vector<DMatch> matches;

inline bool qualitySorting (const KeyPoint& a_, const KeyPoint& b_) { return a_.response < b_.response; }

int main(int argc, char const *argv[])
{
	if (argc != 3)
	{
		cout<<"Two image paths must be specified as arguments"<<std::endl;
		return -1;
	}

	src_1 = imread(argv[1], CV_LOAD_IMAGE_UNCHANGED);
	src_2 = imread(argv[2], CV_LOAD_IMAGE_UNCHANGED);

	//! Grayscaled
	cvtColor(src_1, gray_1, COLOR_BGR2GRAY);
	cvtColor(src_2, gray_2, COLOR_BGR2GRAY);

	if (src_1.data == false || src_2.data == false)
	{
		cout<<"No data"<<std::endl;
		return -1;
	}

	namedWindow(first_src, WINDOW_NORMAL);
	imshow(first_src, src_1);
	namedWindow(second_src, WINDOW_NORMAL);
	imshow(second_src, src_2);
	printf("Press any key\n");
	waitKey(0);
	

	//! Detecting Keypoints through SURF algorithm
	printf("Starting the detections of keypoints\n");
	int minHessian = 800;
	SurfFeatureDetector detector(minHessian);
	detector.detect(src_1, keypoints_1);
	detector.detect(src_2, keypoints_2);
	printf("Done\n");

	//! Sorting the keypoints
	//! I think that they are already sorted, I am wrong?
	printf("Sorting the keypoints\n");
	std::sort(keypoints_1.begin(), keypoints_1.end(), qualitySorting);
	std::sort(keypoints_2.begin(), keypoints_2.end(), qualitySorting);
	std::reverse(keypoints_1.begin(), keypoints_1.end());
	std::reverse(keypoints_2.begin(), keypoints_2.end());
	keypoints_1.resize(50);
	keypoints_2.resize(50);
	printf("Done\n");

	//! Drawing the keypoints
	Mat key_image_1, key_image_2;
	drawKeypoints(src_1, keypoints_1, key_image_1, 
		Scalar::all(-1), 4);
	drawKeypoints(src_2, keypoints_2, key_image_2, 
		Scalar::all(-1),4);

	imshow(first_src, key_image_1);
	imshow(second_src, key_image_2);
	printf("Press any key\n");
	waitKey(0);

	//! Running the extractor
	printf("Running extractor\n");
	Mat desc_1, desc_2;
	SurfDescriptorExtractor extractor;
	extractor.compute(src_1, keypoints_1, desc_1);
	extractor.compute(src_2, keypoints_2, desc_2);
	printf("Done\n");

	//! Running the matcher
	// create a Brute Force matcher
	printf("Brute Force matching\n");
	BFMatcher matcher(NORM_L2, false); // int norm_type, bool Cross-Validation
	matcher.match(desc_1, desc_2, matches);
	//! Drawing matches 1to2
	Mat matched_image;
	drawMatches(src_1, keypoints_1, src_2, keypoints_2, 
		matches, matched_image, Scalar::all(-1), Scalar::all(-1));
	namedWindow(match_window, WINDOW_NORMAL);
	imshow(match_window, matched_image);
	imwrite("../Matched_image.jpg", matched_image);
	printf("Done\n");
	printf("Press any key to end\n");
	waitKey(0);

	return 0;
}
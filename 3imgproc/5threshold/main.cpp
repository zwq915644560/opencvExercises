#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

const char *trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n \
2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
const char *trackbar_value="Value";

int threshold_type=0;
const int maxTypeValue=4;
int threshold_value=3;
const int maxThresholdValue=255;
const int max_BINARY_value = 255;
Mat srcImg; Mat dstImg;

void on_threshold(int, void*);

int main(int argc, char const *argv[])
{
	srcImg=imread("../cat.jpg");
	if(!srcImg.data){cout<<"read failed..."<<endl; return -1;}
	cvtColor( srcImg, srcImg, CV_RGB2GRAY );

	namedWindow("Source Image", WINDOW_AUTOSIZE);
	namedWindow("Treshold Demo", WINDOW_AUTOSIZE);

	createTrackbar(trackbar_type, "Treshold Demo",
		&threshold_type, maxTypeValue, on_threshold);
	createTrackbar(trackbar_value, "Treshold Demo", 
		&threshold_value, maxThresholdValue, on_threshold);

	imshow("Source Image", srcImg);
	on_threshold(0,0);

	waitKey(0);

	destroyWindow("Source Image");
	destroyWindow("Threshold Demo");
	return 0;
}

void on_threshold(int, void *)
{
	/* 0: 二进制阈值
     1: 反二进制阈值
     2: 截断阈值
     3: 0阈值
     4: 反0阈值
   */
	threshold(srcImg, dstImg, threshold_value, max_BINARY_value, threshold_type);
	imshow("Treshold Demo", dstImg);
}
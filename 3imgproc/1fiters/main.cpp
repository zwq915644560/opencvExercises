#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void on_boxBlur(int pos, void *data);
void on_blur(int pos, void *data);
void on_gaussianBlur(int pos, void *data);

int main()
{
	Mat srcImg=imread("../../2core/cat.jpg");
	if(!srcImg.data)
	{
		cout<<"read failed.."<<endl;
		return -1;
	}
	resize(srcImg, srcImg, Size(), 0.4, 0.4);
	
	int boxBlurValue=3;
	int blurValue=3;
	int gaussianBlurValue=3;

	namedWindow("boxBlur", WINDOW_AUTOSIZE);
	createTrackbar("ksize:", "boxBlur", &boxBlurValue,
		40, on_boxFilter, (void *)&srcImg);

	namedWindow("meanBlur", WINDOW_AUTOSIZE);
	createTrackbar("ksize:", "meanBlur", &blurValue,
		40, on_blur, (void *)&srcImg);

	namedWindow("gaussianBlur", WINDOW_AUTOSIZE);
	createTrackbar("ksize:", "gaussianBlur", &gaussianBlurValue,
		40, on_GaussianBlur, (void *)&srcImg);

	on_boxFilter(boxBlurValue, (void *)&srcImg);
	on_blur(blurValue, (void *)&srcImg);
	on_GaussianBlur(gaussianBlurValue, (void *)&srcImg);

	while(waitKey(0)!=27);

	destroyWindow("boxBlur");
	destroyWindow("meanBlur");
	destroyWindow("gaussianBlur");

	return 0;
}

void on_boxFilter(int pos, void *data)
{
	int boxBlurValue=pos;
	Mat dstImg;
	Mat srcImg=*((Mat *)data);
	boxFilter(srcImg, dstImg, -1, Size(boxBlurValue+1, boxBlurValue+1));
	imshow("boxBlur", dstImg);
}
void on_blur(int pos, void *data)
{
	int blurValue=pos;
	Mat dstImg;
	Mat srcImg=*((Mat *)data);
	blur(srcImg, dstImg, Size(blurValue+1, blurValue+1));
	imshow("meanBlur", dstImg);
}
void on_GaussianBlur(int pos, void *data)
{
	int gaussianBlurValue=pos;
	Mat dstImg;
	Mat srcImg=*((Mat *)data);
	GaussianBlur(srcImg, dstImg, Size(gaussianBlurValue*2+1, gaussianBlurValue*2+1), 0, 0);
	imshow("gaussianBlur", dstImg);
}
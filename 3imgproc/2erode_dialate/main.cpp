#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int erosion_elem=0;
int erosion_ksize=0;
int dilation_elem=0;
int dilation_ksize=0;
int maxElem=2;
int maxKernelSize=21;
Mat srcImg;

void on_erode(int pos, void *);
void on_dilate(int pos, void *);

int main(int argc, char **argv)
{
	srcImg=imread(argv[1]);
	if(!srcImg.data)
	{
		cout<<"read failed.."<<endl;
		return -1;
	}
	resize(srcImg, srcImg, Size(), 0.4, 0.4);
	imwrite("../cat.jpg", srcImg);cout<<"cc"<<endl;

	namedWindow("srcImg", WINDOW_AUTOSIZE);
	namedWindow("erosion demo", WINDOW_AUTOSIZE);
	namedWindow("dilation demo", WINDOW_AUTOSIZE);

	createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse",
		"erosion demo", &erosion_elem, maxElem, on_erode);
	createTrackbar("KERNEL Size:\n 2n+1", "erosion demo",
		&erosion_ksize, maxKernelSize, on_erode);
	createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse",
		"dilation demo", &dilation_elem, maxElem, on_dilate);
	createTrackbar("KERNEL Size:\n 2n+1", "dilation demo",
		&dilation_ksize, maxKernelSize, on_dilate);

	on_erode(0,0);//zhudongdiaoyong
	on_dilate(0,0);

	imshow("srcImg", srcImg);

	waitKey(0);

	destroyWindow("srcImg");
	destroyWindow("erosion demo");
	destroyWindow("dilation demo");


	return 0;
}

void on_erode(int , void *)
{
	int erosion_type; 
	if( erosion_elem == 0 ){ erosion_type = MORPH_RECT; } 
	else if( erosion_elem == 1 ){ erosion_type = MORPH_CROSS; } 
	else if( erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }

	Mat element=getStructuringElement(erosion_type,
		Size(2*erosion_ksize+1,2*erosion_ksize+1),
		Point(erosion_ksize, erosion_ksize));

	Mat dstImg;
	erode(srcImg, dstImg, element);

	imshow("erosion demo", dstImg);
}

void on_dilate(int , void *)
{
	int dilation_type; 
	if( dilation_elem == 0 ){ dilation_type = MORPH_RECT; } 
	else if( dilation_elem == 1 ){ dilation_type = MORPH_CROSS; } 
	else if( dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }

	Mat element=getStructuringElement(dilation_type,
		Size(2*dilation_ksize+1,2*dilation_ksize+1),
		Point(dilation_ksize, dilation_ksize));

	Mat dstImg;
	dilate(srcImg, dstImg, element);

	imshow("dilation demo", dstImg);
}

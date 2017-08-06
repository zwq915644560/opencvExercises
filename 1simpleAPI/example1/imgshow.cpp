//#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
using namespace std;
//using namespace cv;

int main(int argc, char *argv[])
{
	cv::Mat img = cv::imread(argv[1],-1);
	if(argc<2)
	{
		cout<<"a picture is needed."<<endl;
		return -1;
	}
	if (img.empty()) 
	{
		cout << "loading image failed "<< endl; 
		return -1;
	}
	cv::namedWindow("example1",cv::WINDOW_AUTOSIZE);
	
	cv::imshow("example1", img);
	cv::waitKey(2000);
	cv::destroyWindow("example1");
	return 0;
}

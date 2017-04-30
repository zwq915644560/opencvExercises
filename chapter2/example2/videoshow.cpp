#include<opencv2/highgui/highgui.hpp>
#include<iostream>
using namespace std; 

int main(int argc,char *argv[])
{
	if(argc<2)
	{
		cout<<"a video is needed."<<endl;
		return -1;
	}
	//cv::VideoCapture cap(argv[1]);
	cv::VideoCapture cap;
	cap.open(argv[1]);
	cv::namedWindow("example2",cv::WINDOW_AUTOSIZE);
	cv::Mat frame;
	for(;;)
	{
		cap>>frame;
		if(frame.empty())
			break;
		cv::imshow("example2",frame);
		if(cv::waitKey(33)>=0)
			break;
		//cv::waitKey(-1);
	}
	return 0;
}
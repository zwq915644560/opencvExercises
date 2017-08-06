#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main(int argc,char *argv[])
{
	VideoCapture cap;
	if(argc==1)
		cap.open(0);
	else if(argc>=2)
		cap.open(argv[1]);
	if(!cap.isOpened())
	{
		cout<<"video stream open failed."<<endl;
		return -1;
	}
	Mat frame,output_gry,output_cny;
	namedWindow("video stream",WINDOW_AUTOSIZE);
	while(true)
	{
		cap>>frame;
		if(frame.empty())
		{
			cout<<"empty."<<endl;
			break;
		}
		cvtColor(frame,output_gry,COLOR_BGR2GRAY);
		Canny(output_gry,output_cny,10,100,3,true);
		imshow("video stream",output_cny);
		if(waitKey(20)>=0)
			break;
	}	
	destroyWindow("video stream");
	return 0;
	
}

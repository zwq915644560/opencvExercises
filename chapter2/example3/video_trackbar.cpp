#include<opencv2/highgui/highgui.hpp>
#include<iostream>

using namespace cv;
using namespace std;

VideoCapture g_cap;
int g_run=1;
int g_click_flag=1;

void onTrackbarSlide(int pos,void *)
{
	g_cap.set(CAP_PROP_POS_FRAMES,pos);
	if(g_click_flag)
		g_run=1;
	g_click_flag=1;
}

int main(int argc, char *argv[])
{
	int slider_position=0;
	
	namedWindow("VideoPlayer",WINDOW_AUTOSIZE);
	if(argc<2)
	{
		cout<<"a video is neede."<<endl;
		return -1;
	}
	g_cap.open(argv[1]);
	int frames=g_cap.get(CAP_PROP_FRAME_COUNT);
	int tmpw = (int) g_cap.get(cv::CAP_PROP_FRAME_WIDTH);
	int tmph = (int) g_cap.get(cv::CAP_PROP_FRAME_HEIGHT);
	cout << "Video has " << frames << " frames of dimensions("
		<< tmpw << ", " << tmph << ")." << endl;

	
	createTrackbar("trackbar","VideoPlayer",&slider_position,
		frames,onTrackbarSlide);
	Mat frame;
	for(;;)
	{
		if(g_run!=0)
		{
			g_cap>>frame;
			if(frame.empty())
			{
				cout<<"empty."<<endl;
				break;
			}
			imshow("VideoPlayer",frame);
			int current_pos=g_cap.get(CAP_PROP_POS_FRAMES);
			g_click_flag=0;
			setTrackbarPos("trackbar","VideoPlayer",current_pos);//
			--g_run;
		}
		char key=(char) waitKey(5);
		if(key=='s')
		{
			g_run=1;
			cout << "Single step, g_run = " << g_run << endl;
		}
		else if(key=='r')
		{
			g_run=-1;
			cout << "Run mode, g_run = " << g_run <<endl;
		}
		else if(key==27)
		{
			cout<<"quit..."<<endl;
			break;
		}
	}
	destroyWindow("VedioPlayer");
	return 0;
}
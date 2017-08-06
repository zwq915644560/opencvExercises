#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main(int argc,char *argv[])
{
	if(argc<3)
	{
		cout<<"need 3 parameters."<<endl;
		return -1;
	}
	VideoCapture cap(argv[1]);
	double fps = cap.get(CAP_PROP_FPS);
	Size size((int)cap.get(CAP_PROP_FRAME_WIDTH ),(int)cap.get(CAP_PROP_FRAME_HEIGHT));
	VideoWriter writer;
	writer.open( argv[2], CV_FOURCC('M','J','P','G'), fps, size );
	Mat logpolar_frame, bgr_frame;
	for(;;)
	{
		cap >> bgr_frame;
		if( bgr_frame.empty() ) 
			break; // end if done
		imshow( "Example2_11", bgr_frame );
		logPolar(bgr_frame,logpolar_frame,Point2f(bgr_frame.cols/2,bgr_frame.rows/2),40,WARP_FILL_OUTLIERS);
		imshow( "Log_Polar", logpolar_frame );
		writer << logpolar_frame;
		char c = waitKey(10);
		if( c == 27 )
			 break; // allow the user to break out
	}
	cap.release();
	return 0;
}

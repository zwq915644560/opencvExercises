#include <opencv2/opencv.hpp>
using namespace cv;

#define WINDOW_NAME "mouse operation"

bool g_bDrawRectangle=false;
Rect g_rectangle(-1,-1,0,0);
RNG g_rng(12345);///

void on_MouseHandle(int event,int x,int y,int flags,void *param);
void drawRectangle(Mat &img, Rect &box);

int main(int argc, char const *argv[])
{
	Mat srcImage(600,800,CV_8UC3);
	Mat tempImage;
	namedWindow(WINDOW_NAME);
	setMouseCallback(WINDOW_NAME,on_MouseHandle,(void *)&srcImage);
	while(1)
	{
		//to reach the result of appearring only one rectangle at everytime of the button down and up.
		//in case that appearring many rectangles during drawing.
		srcImage.copyTo(tempImage);
		if(g_bDrawRectangle)
		{
			drawRectangle(tempImage,g_rectangle);
		}
		imshow(WINDOW_NAME,tempImage);
		if(waitKey(10)==27) 
			break;
	}
	
	return 0;
}
void on_MouseHandle(int event,int x,int y,int flags,void *param)
{
	Mat &img=*((Mat *)param);
	switch(event)
	{
		case EVENT_MOUSEMOVE:
		{
			//when the button is down and mouse move, record the rectangle's width and height.
			if(g_bDrawRectangle)
			{
				g_rectangle.width=x-g_rectangle.x;
				g_rectangle.height=y-g_rectangle.y;
			}
		}break;

		case EVENT_LBUTTONDOWN:
		{
			g_rectangle=Rect(-1,-1,0,0);//clear up the record of the last time
			g_bDrawRectangle=true;
			//when the button is down, record the location.
			g_rectangle.x=x;
			g_rectangle.y=y;
		}break;

		case EVENT_LBUTTONUP:
		{
			g_bDrawRectangle=false;
			//handle the institution of width<0 and height<0. 
			//drawing inversely
			if(g_rectangle.width<0)
			{
				g_rectangle.x+=g_rectangle.width;
				g_rectangle.width*=-1;
			}	
			if(g_rectangle.height<0)
			{
				g_rectangle.y+=g_rectangle.height;
				g_rectangle.height*=-1;
			}	
			//in the first two institution, the rectangle was recorded in tempImage.
			//only when the button is up, draw the rectangle in srcImage.
			//the rectangle was recorded in srcImage.
			drawRectangle(img,g_rectangle);
		}break;

	}
}
void drawRectangle(Mat &img, Rect &box)
{
	rectangle(img,box.tl(),box.br(),
		Scalar(g_rng.uniform(0,255),g_rng.uniform(0,255),g_rng.uniform(0,255)));//change the img everytime;random color
}

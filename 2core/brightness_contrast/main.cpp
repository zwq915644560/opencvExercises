#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int brightValue=100;
int contrastValue=100;
Mat srcImg;


void on_change(int pos, void *data)
{
	Mat dstImg=srcImg.clone();
	int flag=*(int *)data;
	if(flag==0)
		contrastValue=pos;
	else 
		brightValue=pos;
	for(auto it=dstImg.begin<Vec3b>(); it!=dstImg.end<Vec3b>(); ++it)
	{
		for(int i=0; i<3; ++i)
			(*it)[i]=saturate_cast<unsigned char>((contrastValue*0.01)*(*it)[i]
				+(brightValue-100));
	}
	imshow("tuning", dstImg);
}



int main(int argc, char **argv)
{
	srcImg=imread(argv[1]);
	if(!srcImg.data)
	{
		cout<<"read failed.."<<endl;
		return -1;
	}
	resize(srcImg, srcImg, Size(), 0.4, 0.4);
	namedWindow("tuning", WINDOW_AUTOSIZE);
	
	int f0=0,f1=1;
	
	createTrackbar("contrast", "tuning", &contrastValue, 300, on_change, (void *) &f0);
	createTrackbar("brightness", "tuning", &brightValue, 200, on_change, (void *) &f1);

	imshow("tuning", srcImg);

	while(waitKey(0)!=27);

	destroyWindow("tuning");
	return 0;

}
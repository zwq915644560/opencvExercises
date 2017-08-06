#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;

int main(int argc, char *argv[])
{
	cv::Mat input = cv::imread(argv[1],-1);
	if(argc<2)
	{
		cout<<"a picture is needed."<<endl;
		return -1;
	}
	if (input.empty()) 
	{
		cout << "loading image failed "<< endl; 
		return -1;
	}
	cv::namedWindow("input",cv::WINDOW_AUTOSIZE);
	cv::namedWindow("example GaussBlur",cv::WINDOW_AUTOSIZE);
	cv::imshow("input", input);

	cv::Mat output_GaussBlur;
	cv::GaussianBlur( input, output_GaussBlur, cv::Size(5,5), 3, 3);
	cv::imshow("example GaussBlur",output_GaussBlur);
	
	cv::Mat output_gry;
	cv::cvtColor(input,output_gry,cv::COLOR_BGR2GRAY);
	cv::imshow("example gray",output_gry);

	cv::Mat output_cny;
	cv::Canny(output_gry,output_cny,10,100,3,true);
	cv::imshow("example Canny",output_cny);

	cv::Mat output_pyrdown;
	cv::pyrDown(input,output_pyrdown);
	cv::imshow("example pyrdown",output_pyrdown);

	cv::waitKey(0);
	cv::destroyWindow("input");
	cv::destroyWindow("example GaussBlur");
	cv::destroyWindow("example gray");
	cv::destroyWindow("example Canny");
	cv::destroyWindow("example pyrdown");
	
	return 0;
}

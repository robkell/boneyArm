#include "opencv2/highgui/highgui.hpp"
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "ballTracker.hpp"
#include <iostream>
#include <string>

using namespace std;


int main(int ac, char** av)
{
	cout << "OO balltracker example" << endl;
	string arg = av[1];
	cv::VideoCapture capture(arg); 
	if (!capture.isOpened())
        capture.open(atoi(arg.c_str()));

	if (!capture.isOpened())
		{
        		cerr << "Failed to open file/cam!\n"<<endl;
       			return 1;
    		}

	balltracker::balltracker example(capture);
	int i;
	for(i=0; i<100; i++)
	{
		example.processFrame(capture);
	}
	return 0;
}

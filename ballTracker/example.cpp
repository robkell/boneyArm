#include "opencv2/highgui/highgui.hpp"
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "ballTracker.hpp"
#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;


int main(int ac, char** av)
{
	cout << "OO balltracker example" << endl;
	//string arg = av[1];
	cv::VideoCapture capture(0); 
	if (!capture.isOpened())
		{
        		cerr << "Failed to open file/cam!\n"<<endl;
       			return 1;
    		}

	balltracker::balltracker example(capture);
	int i;
	vector<int> pos(3,0); 
	for(;;)
	{
		pos = example.processFrame(capture, false); //PASS TRUE/FALSE AS 2ND ARG TO DISPLAY IMG IN WINDOW
		//usleep(500000);
		if(pos[0]==-1)
		{
			break;
		}
		cout<<"x: "<<pos[0]<<", y: "<<pos[1]<<", radius: "<<pos[2]<<endl;
		
	}
	return 0;
}

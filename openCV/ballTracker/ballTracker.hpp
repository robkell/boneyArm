#ifndef BALLTRACKER_H_
#define BALLTRACKER_H_

#include "opencv2/highgui/highgui.hpp"
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>

//using namespace cv;
namespace balltracker {

class balltracker {
	
	private:
		cv::Mat frame;
	        cv::Mat imghsv;
	        cv::Mat imgthreshed;
	        cv::Mat gray;
		int height;
		int width;
		cv::Size S;
		std::string window_name;
		char filename[200];
	public:
		//cv::VideoCapture& capture;
		balltracker(cv::VideoCapture& capture);
		~balltracker();
		int processFrame(cv::VideoCapture& capture);
		
};

}

#endif //BALLTRACKER_H_

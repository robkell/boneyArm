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
		//std::vector<int> ballPosition;
		cv::VideoCapture cap;
	public:
		balltracker(cv::VideoCapture& capture);
		~balltracker();
		std::vector<int> processFrame(cv::VideoCapture& capture, bool showImage);
		int retHeight(){ return height; };
		int retWidth(){ return width; };
		cv::VideoCapture retCapture(){ return cap; };
};

}

#endif //BALLTRACKER_H_

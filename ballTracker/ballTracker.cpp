#include "opencv2/highgui/highgui.hpp"
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>
#include <stdio.h>
#include "ballTracker.hpp"

using namespace cv;
//using namespace std;

namespace balltracker {

balltracker::balltracker(cv::VideoCapture& capture){
	std::cout << "balltracker constructor" << std::endl;
        
	window_name = "Ball Tracker";
        height = (int) capture.get(CV_CAP_PROP_FRAME_HEIGHT);
        width = (int) capture.get(CV_CAP_PROP_FRAME_WIDTH);

        S = cv::Size(  (int) capture.get(CV_CAP_PROP_FRAME_WIDTH),    
                        (int) capture.get(CV_CAP_PROP_FRAME_HEIGHT)     );

}
    
std::vector<int> balltracker::processFrame(cv::VideoCapture& capture, bool showImage)
    {
            capture >> frame;
            if (frame.empty())
                return std::vector<int>(-1);
		
		//SMOOTHING FILTER AND CONVERT TO HSV COLOUR SPACE
		cv::medianBlur(frame, frame, 5);
		cv::cvtColor(frame,imghsv,CV_RGB2HSV);
		
		//THRESHOLDS
		cv::Mat img(cv::Size(width,height), CV_8UC3);
		cv::Vec3b hsvlower;
		hsvlower[0] = 50; hsvlower[1] = 120; hsvlower[2] = 75;
		cv::Vec3b hsvupper;
		hsvupper[0] = 100; hsvupper[1] = 240; hsvupper[2] = 200;
                cv::Vec3b white;
                white[0] = 255; white[1] = 255; white[2] = 255;
                cv::Vec3b black;
                black[0] = 0; black[1] = 0; black[2] = 0;
		
		//APPLY THRESHOLD
		for (int i=0 ; i < height; ++i){
			for(int j=0 ; j < width; ++j){
				if ((imghsv.at<cv::Vec3b>(i,j)[0] > hsvlower[0])&&(imghsv.at<cv::Vec3b>(i,j)[0] < hsvupper[0])&&(imghsv.at<cv::Vec3b>(i,j)[1] > hsvlower[1])&&(imghsv.at<cv::Vec3b>(i,j)[1] < hsvupper[1])&&(imghsv.at<cv::Vec3b>(i,j)[2] > hsvlower[2])&&(imghsv.at<cv::Vec3b>(i,j)[2] < hsvupper[2])){
					img.at<cv::Vec3b>(i,j) = white;
				}else{
					img.at<cv::Vec3b>(i,j) = black;
				}
			}
	    	}
		
		//CONVERT TO GREYSCALE FORMAT AND FIND CONTOURS
		cv::vector< cv::vector<cv::Point> > contours;
    		cv::vector<cv::Vec4i> hierarchy;
		cv::Mat imgGray;
		cv::cvtColor(img, imgGray, CV_RGB2GRAY);
		cv::findContours( imgGray, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
		cv::vector<cv::Moments> mu(contours.size());
	
		int big=0;
		int currBiggest=0;
		std::vector<int> ballPosition(2,0);
		if( !contours.empty() && !hierarchy.empty() )
		{
		        // iterate through all the top-level contours,
        		for(int i=0; i<contours.size(); i++)
			{
			    int area = cv::contourArea(contours[i]);
			    if(area>currBiggest){
				big=i;
				currBiggest=area;
			    }
			    mu[i] = moments(contours[i], false);
        		}
			//FIND THE CENTER OF MASS FOR THE LARGEST DETECTED OBJECT
       		    	cv::Scalar color( 0, 255, 0 );
       		    	cv::Scalar crossHare( 255, 255, 255 );
//       		    	cv::drawContours( frame, contours, big, color, CV_FILLED, 8, hierarchy );
			int xCenter = mu[big].m10/mu[big].m00;
			int yCenter = mu[big].m01/mu[big].m00;
			//std::cout << "X Coordinate: " << xCenter << "\nY Coordinate: " << yCenter << std::endl;
			ballPosition.at(0) = xCenter; 
			ballPosition.at(1) = yCenter; 
			int lineLength = 10;
			int lineThickness = 2;
			Point top, right, left, bottom;
			top.x = xCenter;
			top.y = yCenter-lineLength;
			right.x = xCenter+lineLength;
			right.y = yCenter;
			bottom.x = xCenter;
			bottom.y = yCenter+lineLength;
			left.x = xCenter-lineLength;
			left.y = yCenter;
			line(frame, top, bottom, crossHare, lineThickness);
			line(frame, left, right, crossHare, lineThickness);
			//std::cout << "X Coordinate: " << ballPosition[0] << ", Y Coordinate: " << ballPosition[1] << std::endl;
    		}
		


		if(showImage)
		{
        		cv::imshow(window_name, frame);
			char key = (char) waitKey(5);//TODO: CHECK THIS, WHY? WHY FRAME DOESNT SHOW WITHOUT?
		}

        return ballPosition;
    }
    

balltracker::~balltracker()
{
        std::cout << "balltracker destructor "<< std::endl;
	//TODO: RELEASE CAPTURE??
}


}//namespace

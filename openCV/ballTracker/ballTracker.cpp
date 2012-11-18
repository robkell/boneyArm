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
        
	window_name = "Tennis Ball Tracker";
        height = (int) capture.get(CV_CAP_PROP_FRAME_HEIGHT);
        width = (int) capture.get(CV_CAP_PROP_FRAME_WIDTH);

        S = cv::Size(  (int) capture.get(CV_CAP_PROP_FRAME_WIDTH),    
                        (int) capture.get(CV_CAP_PROP_FRAME_HEIGHT)     );

}
    
int balltracker::processFrame(cv::VideoCapture& capture)
    {
            capture >> frame;
            if (frame.empty())
                return -1;

		int n = 0;

		cv::medianBlur(frame, frame, 5);

		cv::cvtColor(frame,imghsv,CV_RGB2HSV);

		cv::Mat img(cv::Size(width,height), CV_8UC3);
		cv::Vec3b hsvlower;
		hsvlower[0] = 50; hsvlower[1] = 120; hsvlower[2] = 75;
		cv::Vec3b hsvupper;
		hsvupper[0] = 100; hsvupper[1] = 240; hsvupper[2] = 200;
                cv::Vec3b white;
                white[0] = 255; white[1] = 255; white[2] = 255;
                cv::Vec3b black;
                black[0] = 0; black[1] = 0; black[2] = 0;

		for (int i=0 ; i < height; ++i){
			for(int j=0 ; j < width; ++j){
				if ((imghsv.at<cv::Vec3b>(i,j)[0] > hsvlower[0])&&(imghsv.at<cv::Vec3b>(i,j)[0] < hsvupper[0])&&(imghsv.at<cv::Vec3b>(i,j)[1] > hsvlower[1])&&(imghsv.at<cv::Vec3b>(i,j)[1] < hsvupper[1])&&(imghsv.at<cv::Vec3b>(i,j)[2] > hsvlower[2])&&(imghsv.at<cv::Vec3b>(i,j)[2] < hsvupper[2])){
					img.at<cv::Vec3b>(i,j) = white;
				}else{
					img.at<cv::Vec3b>(i,j) = black;
				}
			}
	    	}

		cv::vector<cv::vector<cv::Point> > contours;
    		cv::vector<cv::Vec4i> hierarchy;
		cv::Mat imgGray;
		cv::cvtColor(img, imgGray, CV_RGB2GRAY);
	
		cv::findContours( imgGray, contours, hierarchy, 
CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );

		cv::Mat dst = cv::Mat::zeros(img.size(), CV_8UC3);
		int big=0;
		int currBiggest=0;
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
        		}
       		    cv::Scalar color( 0, 255, 0 );
       		    cv::drawContours( frame, contours, big, color, 
CV_FILLED, 8, hierarchy );
			
    		}

  //  		cv::imshow( "Connected Components", dst );


            cv::imshow(window_name, frame);
//            imshow("Thresholded", img);
	    
            char key = (char) cv::waitKey(5); //delay N millis

            switch (key)
            {
                case 'q':
                case 'Q':
                case 27: //escape key
                    return 0;
                case ' ': //Save an image
                    sprintf(filename, "filename%.3d.jpg", n++);
                    imwrite(filename, frame);
                    std::cout << "Saved " << filename << std::endl;
                    break;
                default:
                    break;
            }


//        }
	
        return 0;
    }
    

balltracker::~balltracker()
{
        std::cout << "balltracker destructor "<< std::endl;
	//TODO: RELEASE CAPTURE??
}


}//namespace

#include "opencv2/highgui/highgui.hpp"
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>
#include <stdio.h>

using namespace cv;
using namespace std;
    
    int process(VideoCapture& capture)
    {
        int n = 0;
        char filename[200];
        string window_name = "Tennis Ball Tracker";
        cout << "press space to save a picture. q or esc to quit" << endl;
        //namedWindow(window_name, CV_WINDOW_KEEPRATIO); //resizable window;
	int height = (int) capture.get(CV_CAP_PROP_FRAME_HEIGHT);
	int width = (int) capture.get(CV_CAP_PROP_FRAME_WIDTH);
	

	Size S = Size(	(int) capture.get(CV_CAP_PROP_FRAME_WIDTH),    //Acquire input size
                  		(int) capture.get(CV_CAP_PROP_FRAME_HEIGHT)	);    

        Mat frame;
	Mat imghsv;
	Mat imgthreshed;
	Mat gray;

        for (;;)
        {
            capture >> frame;
            if (frame.empty())
                break;

		medianBlur(frame, frame, 5);

		cvtColor(frame,imghsv,CV_RGB2HSV);

		Mat img(Size(width,height), CV_8UC3);
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

		vector<vector<Point> > contours;
    		vector<Vec4i> hierarchy;
		Mat imgGray;
		cvtColor(img, imgGray, CV_RGB2GRAY);

		findContours( imgGray, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );

		Mat dst = Mat::zeros(img.size(), CV_8UC3);
		int big=0;
		int currBiggest=0;
		if( !contours.empty() && !hierarchy.empty() )
		    {
		        // iterate through all the top-level contours,
		        // draw each connected component with its own random color
		       // int idx = 0;
        		//for( ; idx >= 0; idx = hierarchy[idx][0] )
        		for(int i=0; i<contours.size(); i++)
			{
			    int area = contourArea(contours[i]);
			    if(area>currBiggest){
				big=i;
				currBiggest=area;
			    }
        		    //Scalar color( (rand()&255), (rand()&255), (rand()&255) );
        		    //drawContours( dst, contours, i, color, CV_FILLED, 8, hierarchy );
        		}
       		    Scalar color( 0, 255, 0 );
       		    drawContours( frame, contours, big, color, CV_FILLED, 8, hierarchy );
			
    		}

  //  		imshow( "Connected Components", dst );


            imshow(window_name, frame);
//            imshow("Thresholded", img);
	    
            char key = (char) waitKey(5); //delay N millis, usually long enough to disp$

            switch (key)
            {
                case 'q':
                case 'Q':
                case 27: //escape key
                    return 0;
                case ' ': //Save an image
                    sprintf(filename, "filename%.3d.jpg", n++);
                    imwrite(filename, frame);
                    cout << "Saved " << filename << endl;
                    break;
                default:
                    break;
            }


        }
	
        return 0;
    }
    

int main(int ac, char** av)
{
    
    std::string arg = av[1];
    VideoCapture capture(arg); //try to open string, this will attempt to open it as a video file
    if (!capture.isOpened()) //if this fails, try to open as a video camera, through the use of an integer param
        capture.open(atoi(arg.c_str()));
    if (!capture.isOpened())
    {
        cerr << "Failed to open a video device or video file!\n" << endl;
        return 1;
    }
    return process(capture);
}

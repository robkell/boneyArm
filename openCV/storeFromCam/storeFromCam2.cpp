    #include <stdio.h>
    #include <stdlib.h>
    #include "opencv2/opencv.hpp"
    #include "opencv2/highgui/highgui.hpp"

    int main( int argc, char **argv){
        CvCapture *capture = 0;
        IplImage  *frame = 0;
        int       key = 0;

        /* initialize camera */
        capture = cvCaptureFromCAM(0);
        cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 320);
        cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 240);
        //cvSetCaptureProperty(capture, CV_CAP_PROP_FPS, 5);
        /* always check */
        if ( !capture ) {
            fprintf( stderr, "Cannot open initialize webcam!\n" );
            return 1;
        }

        /* create a window for the video */
        //cvNamedWindow( "result", CV_WINDOW_AUTOSIZE );

        while( key != 'q' ) {
            /* get a frame */
            frame = cvQueryFrame( capture );
            /* always check */
            if( !frame )
          {
             break;
             fprintf( stdout, "ERROR: frame is null...\n" );
          }

            /* display current frame */
            //cvShowImage( "result", frame );

            /* exit if user press 'q' */
            key = cvWaitKey( 1 );
        }

        /* free memory */
        //cvDestroyWindow( "result" );
        cvReleaseCapture( &capture );

        return 0;
    }

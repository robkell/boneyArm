#include "./GPIO/gpio.h"
#include "./PWM/cPWM.hpp"
#include "./IK/ik.hpp"
#include "./PID/pid.hpp"
#include "./GPIO/timerutil.h"
#include "./ballTracker/ballTracker.hpp"

#include "opencv2/highgui/highgui.hpp"
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/queue.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <event.h>
#include <cmath>

#define EV_TIMEOUT      0x01
#define EV_READ         0x02
#define EV_WRITE        0x04
#define EV_SIGNAL       0x08
#define EV_PERSIST      0x10
#define EV_ET           0x20

#define OUT		"out"
#define IN		"in"
#define RISING		"rising"
#define FALLING		"falling"
#define BOTH		"both"
#define HIGH		"1"
#define LOW		"0"

#define OPENCLOSE	4
#define WRIST		3
#define ELBOW		2
#define SHOULDER	1
#define LEFTRIGHT	0

//MOTOR RANGES OF OPERATION
#define OPENCLOSE_MAX	100
#define WRIST_MAX	70
#define ELBOW_MAX	0
#define SHOULDER_MAX	250
#define LEFTRIGHT_MAX	210
#define OPENCLOSE_MIN	-100
#define WRIST_MIN	-70
#define ELBOW_MIN	-200
#define SHOULDER_MIN	0
#define LEFTRIGHT_MIN	-210

#define LEFTRIGHT_DPP	0.85
#define SHOULDER_DPP	0.55
#define ELBOW_DPP	0.5
#define WRIST_DPP	0.68

#define LEFTRIGHT_OFFSET	15
#define SHOULDER_OFFSET		165
#define ELBOW_OFFSET		-126
#define WRIST_OFFSET		50
#define OPENCLOSE_OFFSET	0


#define PERIOD		10000000
#define FRAME_RATE_S	0
#define FRAME_RATE_US	100000	// 10fps
using namespace std;

//PIN DECLARATIONS
enum pin{
	P8_1,  P8_2,  P8_3,  P8_4,  P8_5,
	P8_6,  P8_7,  P8_8,  P8_9,  P8_10,
	P8_11, P8_12, P8_13, P8_14, P8_15,
	P8_16, P8_17, P8_18, P8_19, P8_20,
	P8_21, P8_22, P8_23, P8_24, P8_25,
	P8_26, P8_27, P8_28, P8_29, P8_30,
	P8_31, P8_32, P8_33, P8_34, P8_35,
	P8_36, P8_37, P8_38, P8_39, P8_40,
	P8_41, P8_42, P8_43, P8_44, P8_45,
	P8_46,
	P9_1,  P9_2,  P9_3,  P9_4,  P9_5,
	P9_6,  P9_7,  P9_8,  P9_9,  P9_10,
	P9_11, P9_12, P9_13, P9_14, P9_15,
	P9_16, P9_17, P9_18, P9_19, P9_20,
	P9_21, P9_22, P9_23, P9_24, P9_25,
	P9_26, P9_27, P9_28, P9_29, P9_30,
	P9_31, P9_32, P9_33, P9_34, P9_35,
	P9_36, P9_37, P9_38, P9_39, P9_40,
	P9_41, P9_42, P9_43, P9_44, P9_45,
	P9_46
};
class Count  {

    private:
        int MyCount
        int Max
        int Min

    public:
        Count(int min, int max)  {
        	MyCounter = 0;
		Max = max;
		Min = min;
        }
        void setCount(int value)  {
            MyCount = value;
        }
	int operator++(){
		MyCount++;
		return MyCount;
	}
	int operator--(){
		MyCount--;
		return MyCount;
	}
        int GetCount()  {
            return (MyCount);
        }
	bool Check(){
		return ( (MyCount<Max) && (MyCount>Min) );
	}
}
Count leftRightCount(LEFTRIGHT_MIN, LEFTRIGHT_MAX);
Count shoulderCount(SHOULDER_MIN, SHOULDER_MAX);
Count elbowCount(ELBOW_MIN, ELBOW_MAX);
Count wristCount(WRIST_MIN, WRIST_MAX);
Count openCloseCount(OPENCLOSE_MIN, OPENCLOSE_MAX);

/*****************DEFINE DIRECTION GPIOS***************/
gpio::gpio openCloseDir(P8_22);
gpio::gpio wristDir(P8_23);
gpio::gpio elbowDir(P8_24);
gpio::gpio shoulderDir(P8_25);
gpio::gpio leftRightDir(P8_26);
/*****************DEFINE FEEDBACK GPIOS***************/
gpio::gpio openCloseSense(P8_3);
gpio::gpio openCloseCalib(P8_4);
gpio::gpio wristSense(P8_5);
gpio::gpio wristCalib(P8_14);
gpio::gpio elbowSense(P8_8);
gpio::gpio elbowCalib(P8_7);
gpio::gpio shoulderSense(P8_9);
gpio::gpio shoulderCalib(P8_10);
gpio::gpio leftRightSense(P8_11);
gpio::gpio leftRightCalib(P8_12);
/*****************DEFINE SPEED PWMS***************/
cPWM::cPWM openCloseSpeed("ecap.2");
cPWM::cPWM wristSpeed("ehrpwm.2:1");
cPWM::cPWM elbowSpeed("ehrpwm.2:0");
cPWM::cPWM shoulderSpeed("ehrpwm.0:1");
cPWM::cPWM leftRightSpeed("ehrpwm.0:0");
/*****************DEFINE SPEED PWMS***************/
PID::PID openClosePID(OPENCLOSE);
PID::PID wristPID(WRIST);
PID::PID elbowPID(ELBOW);
PID::PID shoulderPID(SHOULDER);
PID::PID leftRightPID(LEFTRIGHT);
/************ Initalize the event library*********/
struct event_base* base = event_base_new();
/*************Instantiate opencv objects**********/
cv::VideoCapture capture(0); 
balltracker::balltracker tracker(capture);

void pinInit();
void exit_handler(int s);
void shoulder_sense_callback(int fd, short event, void *arg);
void leftright_sense_callback(int fd, short event, void *arg);
void elbow_sense_callback(int fd, short event, void *arg);
void wrist_sense_callback(int fd, short event, void *arg);
void openclose_sense_callback(int fd, short event, void *arg);
void shoulder_calib_callback(int fd, short event, void *arg);
void leftright_calib_callback(int fd, short event, void *arg);
void elbow_calib_callback(int fd, short event, void *arg);
void wrist_calib_callback(int fd, short event, void *arg);
void openclose_calib_callback(int fd, short event, void *arg);
void balltracker_callback(int fd, short event, void *arg);

float myRound(float r);

long unsigned timeGlobal;
TimerUtilObj timerObj;

int main(int ac, char** av)
{
        long unsigned time;
        TimerUtil_reset(&timerObj);
        TimerUtil_delta(&timerObj, &time);
	timeGlobal=time;
	
	if (!capture.isOpened())
        {
        	cerr << "Failed to open file/cam!\n"<<endl;
        	return 1;
        }
	balltracker::balltracker* ptracker = &tracker;

	cout << "--------STARTING BONEY ARM-----------" << endl;
	pinInit();	//EXPORTS/CONFIGURES ALL GPIOS AND PWMS
	
	//SIGINT HANDLER
	struct sigaction sigIntHandler;
	sigIntHandler.sa_handler = exit_handler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;
	sigaction(SIGINT, &sigIntHandler, NULL);


	//REGISTER PIN/CAPTURE EVENTS

	int sense_fds[5] = {	leftRightSense.retfd(),
				shoulderSense.retfd(),
				elbowSense.retfd(),
				wristSense.retfd(),
				openCloseSense.retfd()	};
	int calib_fds[5] = {	leftRightSense.retfd(),
				shoulderSense.retfd(),
				elbowSense.retfd(),
				wristSense.retfd(),
				openCloseSense.retfd()	};

	int sense_epfd[5];
	int calib_epfd[5];
        struct epoll_event sense_ev[5];
        struct epoll_event calib_ev[5];

	for (int i=0; i<5;i++)
	{
		sense_epfd[i]=epoll_create(1);
	        printf("epoll_create(1) returned %d: %s\n", sense_epfd[i], strerror(errno));
	        sense_ev[i].events = EPOLLPRI;
        	sense_ev[i].data.fd = sense_fds[i];
        	epoll_ctl(sense_epfd[i], EPOLL_CTL_ADD, sense_fds[i], &sense_ev[i]);

		calib_epfd[i]=epoll_create(1);
	        printf("epoll_create(1) returned %d: %s\n", calib_epfd[i], strerror(errno));
	        calib_ev[i].events = EPOLLPRI;
        	calib_ev[i].data.fd = calib_fds[i];
        	epoll_ctl(calib_epfd[i], EPOLL_CTL_ADD, calib_fds[i], &calib_ev[i]);

	}



        //read initial States to clear readable flag
        int pinVal_lr_calib = leftRightSense.get();
        int pinVal_s_calib = shoulderSense.get();
        int pinVal_e_calib = elbowSense.get();
        int pinVal_w_calib = wristSense.get();
        int pinVal_oc_calib = openCloseSense.get();
        int pinVal_lr_sense = leftRightSense.get();
        int pinVal_s_sense = shoulderSense.get();
        int pinVal_e_sense = elbowSense.get();
        int pinVal_w_sense = wristSense.get();
        int pinVal_oc_sense = openCloseSense.get();
	/*create the events*/
        struct event *ev_leftright_sense_read = event_new(base, sense_epfd[1], EV_READ|EV_PERSIST, leftright_sense_callback, NULL);
        struct event *ev_leftright_calib_read = event_new(base, calib_epfd[1], EV_READ|EV_PERSIST, leftright_calib_callback, NULL);
        struct event *ev_shoulder_sense_read = event_new(base, sense_epfd[2], EV_READ|EV_PERSIST, shoulder_sense_callback, NULL);
        struct event *ev_shoulder_calib_read = event_new(base, calib_epfd[2], EV_READ|EV_PERSIST, shoulder_calib_callback, NULL);
        struct event *ev_elbow_sense_read = event_new(base, sense_epfd[3], EV_READ|EV_PERSIST, elbow_sense_callback, NULL);
        struct event *ev_elbow_calib_read = event_new(base, calib_epfd[3], EV_READ|EV_PERSIST, elbow_calib_callback, NULL);
        struct event *ev_wrist_sense_read = event_new(base, sense_epfd[4], EV_READ|EV_PERSIST, wrist_sense_callback, NULL);
        struct event *ev_wrist_calib_read = event_new(base, calib_epfd[4], EV_READ|EV_PERSIST, wrist_calib_callback, NULL);
        struct event *ev_openclose_sense_read = event_new(base, sense_epfd[5], EV_READ|EV_PERSIST, openclose_sense_callback, NULL);
        struct event *ev_openclose_calib_read = event_new(base, calib_epfd[5], EV_READ|EV_PERSIST, openclose_calib_callback, NULL);

        /* Initalize events */
        event_set(ev_leftright_sense_read, sense_epfd[1], EV_READ|EV_PERSIST, leftright_sense_callback, &ev_leftright_sense_read);
        event_base_set(base, ev_leftright_sense_read);
        event_add(ev_leftright_sense_read, NULL);

	event_set(ev_shoulder_sense_read, sense_epfd[2], EV_READ|EV_PERSIST, shoulder_sense_callback, &ev_shoulder_sense_read);
        event_base_set(base, ev_shoulder_sense_read);
        event_add(ev_elbow_sense_read, NULL);

        event_set(ev_elbow_sense_read, sense_epfd[3], EV_READ|EV_PERSIST, elbow_sense_callback, &ev_elbow_sense_read);
        event_base_set(base, ev_elbow_sense_read);
        event_add(ev_elbow_sense_read, NULL);

        event_set(ev_wrist_sense_read, sense_epfd[4], EV_READ|EV_PERSIST, wrist_sense_callback, &ev_wrist_sense_read);
        event_base_set(base, ev_wrist_sense_read);
        event_add(ev_wrist_sense_read, NULL);

        event_set(ev_openclose_sense_read, sense_epfd[5], EV_READ|EV_PERSIST, openclose_sense_callback, &ev_openclose_sense_read);
        event_base_set(base, ev_openclose_sense_read);
        event_add(ev_openclose_sense_read, NULL);

        event_set(ev_leftright_calib_read, calib_epfd[1], EV_READ|EV_PERSIST, leftright_calib_callback, &ev_leftright_calib_read);
        event_base_set(base, ev_leftright_calib_read);
        event_add(ev_leftright_calib_read, NULL);

	event_set(ev_shoulder_calib_read, calib_epfd[2], EV_READ|EV_PERSIST, shoulder_calib_callback, &ev_shoulder_calib_read);
        event_base_set(base, ev_shoulder_calib_read);
        event_add(ev_elbow_calib_read, NULL);

        event_set(ev_elbow_calib_read, calib_epfd[3], EV_READ|EV_PERSIST, elbow_calib_callback, &ev_elbow_calib_read);
        event_base_set(base, ev_elbow_calib_read);
        event_add(ev_elbow_calib_read, NULL);

        event_set(ev_wrist_calib_read, calib_epfd[4], EV_READ|EV_PERSIST, wrist_calib_callback, &ev_wrist_calib_read);
        event_base_set(base, ev_wrist_calib_read);
        event_add(ev_wrist_calib_read, NULL);

        event_set(ev_openclose_calib_read, calib_epfd[5], EV_READ|EV_PERSIST, openclose_calib_callback, &ev_openclose_calib_read);
        event_base_set(base, ev_openclose_calib_read);
        event_add(ev_openclose_calib_read, NULL);

	/*TIMEOUT EVENT TO GRAB NEXT FRAME*/
	struct event *frame_ev;
	struct timeval rate = { FRAME_RATE_S, FRAME_RATE_US };
	frame_ev = event_new(base, -1, EV_PERSIST, balltracker_callback, (void *)ptracker);
        event_add(frame_ev, &rate);

	event_base_dispatch(base);
        event_base_loop(base, EVLOOP_NONBLOCK);

	return 0;
}

float myRound(float r)
{
        return (r>0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}

void shoulder_sense_callback(int fd, short event, void *arg)
{
	int pinVal = shoulderSense.get();
	if(shoulderDir.retVal()==HIGH){
		shoulderCount++;
	}else{
		shoulderCount--;
	}
}

void leftright_sense_callback(int fd, short event, void *arg)
{
	int pinVal = shoulderSense.get();
	cout << "sense edge!" << endl;
	if(leftRightDir.retVal()==HIGH){
		leftRightCount++;
	}else{
		leftRightCount--;
	}
}

void elbow_sense_callback(int fd, short event, void *arg)
{
	int pinVal = shoulderSense.get();
	if(shoulderDir.retVal()==HIGH){
		shoulderCount++;
	}else{
		shoulderCount--;
	}
}

void wrist_sense_callback(int fd, short event, void *arg)
{
	int pinVal = shoulderSense.get();
	if(shoulderDir.retVal()==HIGH){
		shoulderCount++;
	}else{
		shoulderCount--;
	}
}

void openclose_sense_callback(int fd, short event, void *arg)
{
	int pinVal = shoulderSense.get();
	if(shoulderDir.retVal()==HIGH){
		shoulderCount++;
	}else{
		shoulderCount--;
	}
}

void leftright_calib_callback(int fd, short event, void *arg)
{
	cout << "calib edge!" << endl;
	int pinVal = leftRightCalib.get();
	if(leftRightDir.retVal()==HIGH){
		if(pinVal==0) leftRightCount=LEFTRIGHT_OFFSET;
	}else{
		if(pinVal==1) leftRightCount=LEFTRIGHT_OFFSET;
	}
}

void shoulder_calib_callback(int fd, short event, void *arg)
{
	int pinVal = shoulderCalib.get();
	if(shoulderDir.retVal()==HIGH){
		if(pinVal==0) shoulderCount=SHOULDER_OFFSET;
	}else{
		if(pinVal==1) shoulderCount=SHOULDER_OFFSET;
	}
}

void elbow_calib_callback(int fd, short event, void *arg)
{
	int pinVal = elbowCalib.get();
	if(elbowDir.retVal()==HIGH){
		if(pinVal==0) elbowCount=ELBOW_OFFSET;
	}else{
		if(pinVal==1) elbowCount=ELBOW_OFFSET;
	}
}

void wrist_calib_callback(int fd, short event, void *arg)
{
	int pinVal = wristCalib.get();
	if(wristDir.retVal()==HIGH){
		if(pinVal==0) wristCount=WRIST_OFFSET;
	}else{
		if(pinVal==1) wristCount=WRIST_OFFSET;
	}
}

void openclose_calib_callback(int fd, short event, void *arg)
{
	int pinVal = openCloseCalib.get();
	if(openCloseDir.retVal()==HIGH){
		if(pinVal==0) openCloseCount=OPENCLOSE_OFFSET;
	}else{
		if(pinVal==1) openCloseCount=OPENCLOSE_OFFSET;
	}
}
void balltracker_callback(int fd, short event, void *arg)
{
	//return ball position every 200ms
	cout << "Updating ball position..." <<endl;
	vector<int> pos(3,0);	//{x,y,radius};
	//balltracker::balltracker tracker = *(balltracker::balltracker *)arg;
	//cv::VideoCapture capture = tracker.retCapture();
	
	pos = tracker.processFrame(capture, false); //PASS TRUE/FALSE AS 2ND ARG TO DISPLAY IMG IN WINDOW
	float W = (float)tracker.retWidth();
	float H =(float)tracker.retHeight();
	//cout << "W = " << W << endl;
	//cout << "H = " << H << endl;
	cout << "pos = <" <<pos[0]<<", "<<pos[1]<<", "<<pos[2]<<">"<< endl;


	//DETECTED OBJECT OFFSETS FROM CENTER NORMALISED TO FRAME DIMENSIONS
	float x_offset = ((pos[0] - (W/2))/W)*2;
	//cout << "x_offset = " << x_offset << endl;
	float y_offset = ((pos[1] - (H/2))/H)*2;
	
	if(x_offset<0)
	{
		leftRightDir.set(LOW);
		x_offset=abs(x_offset);
	}else{
		leftRightDir.set(HIGH);
	}
	if(x_offset<0.05)
	{
		leftRightSpeed.Duty(0);
	}else{
		x_offset=x_offset+0.15;
		if(x_offset>1)x_offset=1;
		leftRightSpeed.Duty(x_offset*PERIOD);
	}

	if(y_offset<0)
	{
		shoulderDir.set(LOW);
		elbowDir.set(LOW);
		wristDir.set(LOW);
		y_offset=abs(y_offset);
	}else{
		shoulderDir.set(HIGH);
		elbowDir.set(HIGH);
		wristDir.set(HIGH);
	}
	if(y_offset<0.05)
	{
		shoulderSpeed.Duty(0);
		elbowSpeed.Duty(0);
		wristSpeed.Duty(0);
	}else{
		y_offset=y_offset+0.15;
		if(y_offset>1)y_offset=1;
		
		if(y_offset<0.3){
			//drive 1 motor
			if(wristCount.check()){
				wristSpeed.Duty(y_offset);
			} else if(elbowCount.check()){
				elbowSpeed.Duty(y_offset);
			} else if(shoulderCount.check()){
				shoulderSpeed.Duty(y_offset);
			}

		} else if (Y_offset<0.6){
			//drive 2 motors
			if(wristCount.check() && elbowCount.check()){
				wristSpeed.Duty(y_offset);
				elbowSpeed.Duty(y_offset);
			} else if(wristCount.check() && shoulderCount.check()){
				wristSpeed.Duty(y_offset);
				shoulderSpeed.Duty(y_offset);
			} else if(shoulderCount.check() && elbowCount.check()){
				elbowSpeed.Duty(y_offset);
				shoulderSpeed.Duty(y_offset);
			}
		} else {
			//drive all 3
			if(wristCount.check()) wristSpeed.Duty(y_offset);
			if(elbowCount.check()) elbowSpeed.Duty(y_offset);
			if(shoulderCount.check()) shoulderSpeed.Duty(y_offset);
		}
	}

}

/*
void motorInit(gpio::gpio *sense, gpio::gpio *calib, gpio::gpio *direction, cPWM::cPWM *speed)
{
	direction.direction(OUT);
	direction.set(LOW);
	sense.direction(IN);
	sense.edge(RISING);
	calib.direction(IN);
	calib.edge(BOTH);

	speed.Request(1);
	speed.Period(PERIOD);
	speed.Duty(0);
	speed.Polarity(0);
	speed.Run();
}
*/
void pinInit()
{
	cout << "--------INITIALISING GPIO'S----------" << endl;

	openCloseDir.direction(OUT);
	openCloseSense.direction(IN);
	openCloseSense.edge(RISING);
	openCloseCalib.direction(IN);
	openCloseCalib.edge(BOTH);
	openCloseDir.set(LOW);

	wristDir.direction(OUT);
	wristSense.direction(IN);
	wristSense.edge(RISING);
	wristCalib.direction(IN);
	wristCalib.edge(BOTH);
	wristDir.set(LOW);

	elbowDir.direction(OUT);
	elbowSense.direction(IN);
	elbowSense.edge(RISING);
	elbowCalib.direction(IN);
	elbowCalib.edge(BOTH);
	elbowDir.set(LOW);

	shoulderDir.direction(OUT);
	shoulderSense.direction(IN);
	shoulderSense.edge(RISING);
	shoulderCalib.direction(IN);
	shoulderCalib.edge(BOTH);
	shoulderDir.set(LOW);

	leftRightDir.direction(OUT);
	leftRightSense.direction(IN);
	leftRightSense.edge(RISING);
	leftRightCalib.direction(IN);
	leftRightCalib.edge(BOTH);
	leftRightDir.set(LOW);

	//SET PWM DEFAULTS
	cout << "--------INITIALISING PWM'S-----------" << endl;
	openCloseSpeed.Request(	1);
	openCloseSpeed.Period(PERIOD);
	openCloseSpeed.Duty(0);
	openCloseSpeed.Polarity(0);
	openCloseSpeed.Run();

	wristSpeed.Request(1);
	wristSpeed.Period(PERIOD);
	wristSpeed.Duty(0);
	wristSpeed.Polarity(0);
	wristSpeed.Run();

	elbowSpeed.Request(	1);
	elbowSpeed.Period(PERIOD);
	elbowSpeed.Duty(0);
	elbowSpeed.Polarity(0);
	elbowSpeed.Run();

	shoulderSpeed.Request(	1);
	shoulderSpeed.Period(PERIOD);
	shoulderSpeed.Duty(0);
	shoulderSpeed.Polarity(0);
	shoulderSpeed.Run();

	leftRightSpeed.Request(	1);
	leftRightSpeed.Period(PERIOD);
	leftRightSpeed.Duty(0);
	leftRightSpeed.Polarity(0);
	leftRightSpeed.Run();

}

void exit_handler(int s){
	printf("Caught signal %d\n",s);
        event_base_free(base);   
	exit(1); 

}

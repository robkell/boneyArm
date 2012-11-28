#include "gpio.h"
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
#include <timerutil.h>
#include <event.h>

#define EV_TIMEOUT      0x01
#define EV_READ         0x02
#define EV_WRITE        0x04
#define EV_SIGNAL       0x08
#define EV_PERSIST      0x10
#define EV_ET           0x20

using namespace std;

enum pin
        {
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

pin testPin = P8_46;
gpio::gpio dir1(testPin);
long unsigned timeG;

int posedge, file, exportfd, loopCount, count=0;
TimerUtilObj timerObj;

static void my_cb(int fd, short event, void *arg);

int main()
{
	long unsigned time;
	cout << "this is a test\n";
	dir1.direction("in");		//CONFIG AS INPUT
	dir1.edge("rising");		//CONFIG INTERUPTS ON RISING EDGE
	
	TimerUtil_reset(&timerObj);
	TimerUtil_delta(&timerObj, &time);
	timeG=time;
        printf("starttime = %ld\n", timeG);
	file = dir1.retfd();
	
	// Create epoll event
	int epfd = epoll_create(1);
	printf("epoll_create(1) returned %d: %s\n", epfd, strerror(errno));
	struct epoll_event ev;
	ev.events = EPOLLPRI;
	ev.data.fd = file;
	int n = epoll_ctl(epfd, EPOLL_CTL_ADD, file, &ev);
	
	//read initial State
	int pinVal = dir1.get();

	/* Initalize the event library */
	struct event_base* base = event_base_new();

	/*create the event*/
	struct event *ev_file_read = event_new(base, epfd, EV_READ|EV_PERSIST, my_cb, NULL);

	/* Initalize one event */
	event_set(ev_file_read, epfd, EV_READ|EV_PERSIST, my_cb, &ev_file_read);
	event_base_set(base, ev_file_read);
	event_add(ev_file_read, NULL);
	event_base_dispatch(base);
	event_base_loop(base, EVLOOP_NONBLOCK);

	/*
	TimerUtil_delta(&timerObj, &time);
	timeG=time;
        printf("endtime = %ld\n", timeG);
	*/
	return 0;
}


       static void
        my_cb(int fd, short event, void *arg)
        {
		long unsigned time;
		time=timeG;
                int m = 0;
                char buf[64];
                m = lseek(file, 0, SEEK_SET);
                m = read(file, &buf, 63);
                buf[m] = 0;
//              printf("Edge detected, value = %s\n", buf);

                int num = atoi(buf);
                if(num == 1){
//                      printf("rising edge\n");
                        TimerUtil_delta(&timerObj, &time);
                        float delta = time;
                        float freq = 1000000*(1/delta);
                        printf("frequency = %fHz\n", freq);
                        count++;

                };
                if(count==10){
                        printf("count = %i\n", count);
               };
        }




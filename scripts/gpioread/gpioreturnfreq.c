	/*
	 * Compile with:
	 * cc -I/usr/local/include -o signal-test \
	 *   signal-test.c -L/usr/local/lib -levent
	 */
	
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <sys/queue.h>
	#include <unistd.h>
	#include <sys/time.h>
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

	int count=0;
	int samples=3;
	int file;
	long time;
        TimerUtilObj timerObj;
	float frequency;
	float freq;
	struct event *ev_file_read;

	static void
	my_cb(int fd, short event, void *arg)
	{

		if (event & EV_TIMEOUT) {
			printf("0");
			exit(1);
		}

 		int m = 0;
        	char buf[64];
        	m = lseek(file, 0, SEEK_SET);
        	m = read(file, &buf, 63);
        	buf[m] = 0;
		
		int num = atoi(buf);
		if(num == 1){
			TimerUtil_delta(&timerObj, &time);
			float delta = time;
			freq = 1000000*(1/delta);
			count=count+1;
		};

		if (count==samples){
			frequency = freq;
			printf("%f", frequency);
			struct event_base *base = arg;
			event_base_loopbreak(base);
		        event_del(ev_file_read);

		};

	}
	
	int
	main (int argc, char **argv)
	{
	        int loopCount;
		char* filename = argv[1];

	        TimerUtil_reset(&timerObj);
	        TimerUtil_delta(&timerObj, &time);

		file = open( filename , O_RDWR | O_NONBLOCK);

	        // Create epoll event
	        int epfd = epoll_create(1);
	        struct epoll_event ev;
	        ev.events = EPOLLPRI;
	        ev.data.fd = file;
	        int n = epoll_ctl(epfd, EPOLL_CTL_ADD, file, &ev);

	        // Read initial state
	        int m = 0;
	        char buf[64];
	        m = lseek(file, 0, SEEK_SET);
	        m = read(file, &buf, 63);
	        buf[m] = 0;

	        /* Initalize the event library */
	        struct event_base* base = event_base_new();
		
		struct timeval tv;
		tv.tv_sec = 0;
  		tv.tv_usec = 500000;
		
		/*create the event*/	
		ev_file_read = event_new(base, epfd, EV_READ|EV_PERSIST|EV_TIMEOUT, my_cb, NULL);

	        /* Initalize one event */
	        event_set(ev_file_read, epfd, EV_TIMEOUT|EV_READ|EV_PERSIST, my_cb, &ev_file_read);
	        event_base_set(base, ev_file_read);
	        event_add(ev_file_read, &tv);
	        event_base_dispatch(base);
	        event_base_loop(base, EVLOOP_NONBLOCK);

//	        event_base_free(base);
	        return frequency;
	}

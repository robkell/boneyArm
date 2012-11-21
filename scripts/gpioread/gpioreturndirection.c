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
	int file1;
	int file2;
	long time;
	long delta[3];
        TimerUtilObj timerObj;
	struct event *ev_file_read1;
	struct event *ev_file_read2;

	static void
	my_cb1(int fd, short event, void *arg)
	{
  		if (event & EV_TIMEOUT) {
  			printf("0");
    			exit(1);
  		}

 		int m = 0;
        	char buf[64];
        	m = lseek(file1, 0, SEEK_SET);
        	m = read(file1, &buf, 63);
        	buf[m] = 0;
		
		int num = atoi(buf);
		if(num == 1){
			TimerUtil_delta(&timerObj, &time);
			delta[count] = time;
			//printf("rising edge fb1: %i\n", time);
			count++;
		};

		if (count==samples){
			if(delta[1]>delta[2]){
				printf("forward");
			}else{
				printf("backward");			
			};
			struct event_base *base = arg;
			event_base_loopbreak(base);
		        event_del(ev_file_read1);
		        event_del(ev_file_read2);
		};

	}
	static void
	my_cb2(int fd, short event, void *arg)
	{
  		if (event & EV_TIMEOUT) {
  			printf("0");
    			exit(1);
  		}

 		int m = 0;
        	char buf[64];
        	m = lseek(file2, 0, SEEK_SET);
        	m = read(file2, &buf, 63);
        	buf[m] = 0;
		
		int num = atoi(buf);
		if(num == 1){
			//printf("rising edge fb2\n");
			TimerUtil_delta(&timerObj, &time);
			delta[count] = time;
			count++;
		};

		if (count==samples){
			if(delta[1]>delta[2]){
				printf("backward");			
			}else{
				printf("forward");
			};
			struct event_base *base = arg;
			event_base_loopbreak(base);
		        event_del(ev_file_read1);
		        event_del(ev_file_read2);
		};

	}
	
	int
	main (int argc, char **argv)
	{
		char* filename1 = argv[1];
		char* filename2 = argv[2];

	        TimerUtil_reset(&timerObj);
	        TimerUtil_delta(&timerObj, &time);

		file1 = open( filename1 , O_RDWR | O_NONBLOCK);
		file2 = open( filename2 , O_RDWR | O_NONBLOCK);

	        // Create epoll event
	        int epfd1 = epoll_create(1);
	        int epfd2 = epoll_create(1);

	        struct epoll_event ev1;
	        ev1.events = EPOLLPRI;
	        ev1.data.fd = file1;
	        int n1 = epoll_ctl(epfd1, EPOLL_CTL_ADD, file1, &ev1);

	        struct epoll_event ev2;
	        ev2.events = EPOLLPRI;
	        ev2.data.fd = file2;
	        int n2 = epoll_ctl(epfd2, EPOLL_CTL_ADD, file2, &ev2);

	        // Read initial state
	        int m1 = 0;
	        char buf1[64];
	        m1 = lseek(file1, 0, SEEK_SET);
	        m1 = read(file1, &buf1, 63);
	        buf1[m1] = 0;

	        // Read initial state
	        int m2 = 0;
	        char buf2[64];
	        m2 = lseek(file2, 0, SEEK_SET);
	        m2 = read(file2, &buf2, 63);
	        buf2[m2] = 0;

		struct timeval tv;

		tv.tv_sec = 0;
		tv.tv_usec = 500000;

	        /* Initalize the event library */
	        struct event_base* base = event_base_new();

		/*create the event*/	
		ev_file_read1 = event_new(base, epfd1, EV_TIMEOUT|EV_READ|EV_PERSIST, my_cb1, NULL);
		ev_file_read2 = event_new(base, epfd2, EV_TIMEOUT|EV_READ|EV_PERSIST, my_cb2, NULL);


	        /* Initalize first event */
	        event_set(ev_file_read1, epfd1, 
EV_TIMEOUT|EV_READ|EV_PERSIST, 
my_cb1, &ev_file_read1);
	        event_base_set(base, ev_file_read1);
	        event_add(ev_file_read1, &tv);
	        /* Initalize second event */
	        event_set(ev_file_read2, epfd2, 
EV_TIMEOUT|EV_READ|EV_PERSIST, 
my_cb2, &ev_file_read2);
	        event_base_set(base, ev_file_read2);
	        event_add(ev_file_read2, &tv);

	        event_base_dispatch(base);
	        event_base_loop(base, EVLOOP_NONBLOCK);

	        return (0);
	}

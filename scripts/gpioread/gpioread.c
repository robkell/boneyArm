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

	int posedge;
	int file;
	long time;
        TimerUtilObj timerObj;
	int count=0;
	
	static void
	my_cb(int fd, short event, void *arg)
	{
 		int m = 0;
        	char buf[64];
        	m = lseek(file, 0, SEEK_SET);
        	m = read(file, &buf, 63);
        	buf[m] = 0;
//        	printf("Edge detected, value = %s\n", buf);
		
		int num = atoi(buf);
		if(num == 1){
//			printf("rising edge\n");
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
	
	int
	main (int argc, char **argv)
	{
	        int loopCount;
//		printf("file = %s\n", filename);

	        TimerUtil_reset(&timerObj);
	        TimerUtil_delta(&timerObj, &time);
	       //printf("starttime = %ld\n", time);

		//filename = "/sys/class/gpio/gpio34/value"
		file = open( "/sys/class/gpio/gpio44/value" , O_RDWR | 
O_NONBLOCK);

	        // Create epoll event
	        int epfd = epoll_create(1);
	        printf("epoll_create(1) returned %d: %s\n", epfd, strerror(errno));
	        struct epoll_event ev;
	        ev.events = EPOLLPRI;
	        ev.data.fd = file;
	        int n = epoll_ctl(epfd, EPOLL_CTL_ADD, file, &ev);

	        // Read initial state
	        int m = 0;
	        char buf[64];
	        m = lseek(file, 0, SEEK_SET);
	        printf("seek(%d) %d bytes: %s\n", file, m, strerror(errno));
	        m = read(file, &buf, 63);
	        buf[m] = 0;
	        printf("read(%d) %d bytes (%s): %s\n", file, m, buf, strerror(errno));

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

//	        event_base_free(base);
	        return (0);
	}

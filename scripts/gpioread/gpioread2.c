
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

	#include <event.h>

	int called = 0;

int file = open( "/sys/class/gpio/gpio34/value" , O_RDWR | O_NONBLOCK);	
void cb_func(evutil_socket_t fd, short what, void *arg)
{
        const char *data = arg;
        printf("Got an event on socket %d:%s%s%s%s [%s]",
            (int) fd,
            (what&EV_TIMEOUT) ? " timeout" : "",
            (what&EV_READ)    ? " read" : "",
            (what&EV_WRITE)   ? " write" : "",
            (what&EV_SIGNAL)  ? " signal" : "",
            data);
}

void main_loop(evutil_socket_t fd1, evutil_socket_t fd2)
{
        struct event *ev1, *ev2;
        struct timeval five_seconds = {5,0};
        struct event_base *base = event_base_new();

        /* The caller has already set up fd1, fd2 somehow, and make them
           nonblocking. */

        ev1 = event_new(base, fd1, EV_TIMEOUT|EV_READ|EV_PERSIST, cb_func,
           (char*)"Reading event");
        ev2 = event_new(base, fd2, EV_WRITE|EV_PERSIST, cb_func,
           (char*)"Writing event");

        event_add(ev1, &five_seconds);
        event_add(ev2, NULL);
        event_base_dispatch(base);
}

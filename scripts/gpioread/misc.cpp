#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <ev.h>

/*Configure gpio through Sysfs 
int p = 0;
char bufp = "34";
int fdp = open("/sys/class/gpio/export", O_RDWR | O_NONBLOCK);
p = write(fdp, buf, 63);
int p1 = 0;
char bufp1 = "input";
int fdp1 = open("/sys/class/gpio/gpio34/direction", O_RDWR | O_NONBLOCK);
p1 = write(fdp1, &buf, 63);
int p2 = 0;
char bufp2 = "both";
int fdp2 = open("/sys/class/gpio/gpio34/edge", O_RDWR | O_NONBLOCK);
p2 = write(fdp2, &buf, 63);
close(fdp);
close(fdp1);
close(fdp2);
*/

// Open file to watch
int fd = open("/sys/class/gpio/gpio34/value", O_RDWR | O_NONBLOCK);

static void my_cb (EV_P_ ev_io *w, int revents)
{
	int m = 0;
        char buf[64];
        m = lseek(fd, 0, SEEK_SET);
//        printf("seek(%d) %d bytes: %s\n", fd, m, strerror(errno));
        m = read(fd, &buf, 63);
        buf[m] = 0;
//        printf("read(%d) %d bytes (%s): %s\n", fd, m, buf, strerror(errno));
	printf("Edge detected, value = %s", buf);
}

int main(void){

        printf("open(%s) returned %d: %s\n", "/sys/class/gpio/gpio34/value", fd, strerror(errno));
        
        // Create epoll event
        int epfd = epoll_create(1);
        printf("epoll_create(1) returned %d: %s\n", epfd, strerror(errno));
        struct epoll_event ev;
        ev.events = EPOLLPRI;
        ev.data.fd = fd;
        int n = epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);
        printf("epoll_ctl(%d) returned %d (%d): %s\n", fd, n, epfd, strerror(errno));

        // Read initial state
        int m = 0;
        char buf[64];
        m = lseek(fd, 0, SEEK_SET);
        printf("seek(%d) %d bytes: %s\n", fd, m, strerror(errno));
        m = read(fd, &buf, 63);
        buf[m] = 0;
        printf("read(%d) %d bytes (%s): %s\n", fd, m, buf, strerror(errno));
	
        // Setup event watcher

	struct ev_loop *loop = ev_default_loop(0);
	struct ev_io event_watcher;
	ev_init (&event_watcher, my_cb);
	ev_io_set (&event_watcher, epfd, EV_READ);
	ev_io_start (loop, &event_watcher);
	ev_loop (loop, 0);

	return 0;

}


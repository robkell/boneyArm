#include <stdio.h>
#include <stdlib.h>

#include <timerutil.h>

int main(int argc, char *argv[])
{
	long time;
	TimerUtilObj timerObj;
	int loopCount;

	TimerUtil_reset(&timerObj);
	TimerUtil_delta(&timerObj, &time);
	printf("starttime = %ld\n", time);
	
	sleep(5);

	TimerUtil_delta(&timerObj, &time);
	printf("endtime = %ld\n", time);

	return 1;
}

#include "pid.hpp"
#include <iostream>
#include "timerutil.h"

using namespace std;

int main()
{
	TimerUtilObj timerObj;
	long unsigned time;
        TimerUtil_reset(&timerObj);
        TimerUtil_delta(&timerObj, &time);


	cout << "PID example" << endl;
	//PID::PID* x;
	//x = new PID::PID(1);
	PID::PID x(1);
	int i;
	int res;
	for(i=0;i<20200;i=i+100)
	{
		TimerUtil_delta(&timerObj, &time);
		res = x.calcPID(20000, i, time);
		cout << "PID = " << res << endl;
	}

	return 1;

}


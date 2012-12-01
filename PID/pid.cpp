#include "pid.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

#define LOW_LIMIT	10

namespace PID {


PID::PID(int id)
{
	std::cout << "called PID constructor" << std::endl;
	PID::id = id;
	//srand ( time(NULL) );

}

int PID::calcPID(int dest, int pos, long dt)
{
		prev_error=current_error;
		PID::dest = dest;
		PID::pos = pos;
		
		current_error=dest-pos;
		P=current_error;
		std::cout << "P: " << (P*Kp) << std::endl;
		//TODO: add dt calc

		//int dt = rand()%10 + 1;
		//std::cout << dt << std::endl;

		PID::D=(current_error-prev_error)/dt;
		PID::I+=(current_error*dt);
		std::cout << "D: " << (D*Kd) << std::endl;
		std::cout << "I: " << (I*Ki) << std::endl;
		pid = (Kp*P + Ki*I + Kd*D);
		
		//SATURATE THE RETURN DUTY CYCLE TO +/-100
		if(pid>100)
		{
			pid=100;
		};
		if(pid<-100)
		{
			pid=-100;
		};

		//TODO: Add deadband Calc
		if(abs(pid)<LOW_LIMIT)
		{
			return 0;
		}
		return pid;
}

PID::~PID()
{
	std::cout << "PID "<< PID::id << " destructor called" << std::endl;
}

} /* namespace PID */

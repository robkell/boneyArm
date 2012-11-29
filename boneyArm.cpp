#include "./GPIO/gpio.h"
#include "./PWM/cPWM.hpp"
#include "./IK/ik.hpp"
#include "./PID/pid.hpp"
#include "./GPIO/timerutil.h"

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
/*****************DEFINE DIRECTION GPIOS***************/
gpio::gpio openCloseDir(P8_22);
gpio::gpio wristDir(P8_23);
gpio::gpio elbowDir(P8_24);
gpio::gpio shoulderDir(P8_25);
gpio::gpio leftRighDir(P8_26);
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

void pinInit();

int main()
{
	cout << "--------STARTING BONEY ARM-----------" << endl;
	pinInit();	//EXPORTS/CONFIGURES ALL GPIOS AND PWMS

	shoulderSpeed.Run();
	shoulderDir.set(LOW);
	sleep(2);
	shoulderDir.set(HIGH);
	sleep(2);
	shoulderDir.set(LOW);
	sleep(2);
	shoulderDir.set(HIGH);
	sleep(2);
	shoulderDir.set(LOW);
	sleep(2);
	shoulderSpeed.Stop();

	return 0;
}


void pinInit()
{
	cout << "--------INITIALISING GPIO'S----------" << endl;

	openCloseDir.direction(OUT);
	openCloseSense.direction(IN);
	openCloseSense.edge(RISING);
	openCloseCalib.direction(IN);
	openCloseCalib.edge(BOTH);
	
	wristDir.direction(OUT);
	wristSense.direction(IN);
	wristSense.edge(RISING);
	wristCalib.direction(IN);
	wristCalib.edge(BOTH);
	
	elbowDir.direction(OUT);
	elbowSense.direction(IN);
	elbowSense.edge(RISING);
	elbowCalib.direction(IN);
	elbowCalib.edge(BOTH);
	
	shoulderDir.direction(OUT);
	shoulderSense.direction(IN);
	shoulderSense.edge(RISING);
	shoulderCalib.direction(IN);
	shoulderCalib.edge(BOTH);
	
	leftRighDir.direction(OUT);
	leftRightSense.direction(IN);
	leftRightSense.edge(RISING);
	leftRightCalib.direction(IN);
	leftRightCalib.edge(BOTH);

	//SET PWM DEFAULTS
	cout << "--------INITIALISING PWM'S-----------" << endl;
	openCloseSpeed.Request(	1);
	openCloseSpeed.Period(	10000000);
	openCloseSpeed.Duty(	 5000000);
	openCloseSpeed.Polarity(0);

	wristSpeed.Request(	1);
	wristSpeed.Period(	10000000);
	wristSpeed.Duty(	 5000000);
	wristSpeed.Polarity(0);

	elbowSpeed.Request(	1);
	elbowSpeed.Period(	10000000);
	elbowSpeed.Duty(	 5000000);
	elbowSpeed.Polarity(0);

	shoulderSpeed.Request(	1);
	shoulderSpeed.Period(	10000000);
	shoulderSpeed.Duty(	 5000000);
	shoulderSpeed.Polarity(0);

	leftRightSpeed.Request(	1);
	leftRightSpeed.Period(	10000000);
	leftRightSpeed.Duty(	 5000000);
	leftRightSpeed.Polarity(0);

}

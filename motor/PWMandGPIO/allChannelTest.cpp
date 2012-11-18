#include "cPWM.h"
#include <iostream>
#include <unistd.h>
#include <string>
using namespace std;

int main()
{
	cPWM::cPWM* ch1Speed;
	cPWM::cPWM* ch2Speed;
	cPWM::cPWM* ch3Speed;
	cPWM::cPWM* ch4Speed;
	cPWM::cPWM* ch5Speed;
	cPWM::cPWM* ch6Speed;
	cPWM::cPWM* ch7Speed;
	cPWM::cPWM* ch8Speed;
	string ch1, ch2, ch3, ch4, ch5, ch6 , ch7, ch8;
	
	ch1 = "ehrpwm0.0";
	ch2 = "ehrpwm0.1";
	ch3 = "ecap.0";
	ch4 = "ehrpwm1.0";
	ch5 = "ehrpwm1.1";
	ch6 = "ehrpwm2.0";
	ch7 = "ehrpwm2.1";
	ch8 = "ecap.2";

	ch1Speed = new cPWM::cPWM(ch1);
	ch2Speed = new cPWM::cPWM(ch2);
	ch3Speed = new cPWM::cPWM(ch3);
	ch4Speed = new cPWM::cPWM(ch4);
	ch5Speed = new cPWM::cPWM(ch5);
	ch6Speed = new cPWM::cPWM(ch6);
	ch7Speed = new cPWM::cPWM(ch7);
	ch8Speed = new cPWM::cPWM(ch8);
	
	//RUN CH1
	ch1Speed->Request(1);
	ch1Speed->Period(20000000);
	ch1Speed->Duty(1000000);
	ch1Speed->Polarity(1);
	ch1Speed->Run();
	//RUN CH2
	ch2Speed->Request(1);
	ch2Speed->Period(20000000);
	ch2Speed->Duty(  1000000);
	ch2Speed->Polarity(1);
	ch2Speed->Run();
	//RUN CH3
	ch3Speed->Request(1);
	ch3Speed->Period(20000000);
	ch3Speed->Duty(  1000000);
	ch3Speed->Polarity(1);
	ch3Speed->Run();
	//RUN CH4
	ch4Speed->Request(1);
	ch4Speed->Period(20000000);
	ch4Speed->Duty(  1000000);
	ch4Speed->Polarity(1);
	ch4Speed->Run();
	//RUN CH5
	ch5Speed->Request(1);
	ch5Speed->Period(20000000);
	ch5Speed->Duty(  1000000);
	ch5Speed->Polarity(1);
	ch5Speed->Run();
	//RUN CH6
	ch6Speed->Request(1);
	ch6Speed->Period(20000000);
	ch6Speed->Duty(  1000000);
	ch6Speed->Polarity(1);
	ch6Speed->Run();
	//RUN CH7
	ch7Speed->Request(1);
	ch7Speed->Period(20000000);
	ch7Speed->Duty(  1000000);
	ch7Speed->Polarity(1);
	ch7Speed->Run();
	//RUN CH8
	ch8Speed->Request(1);
	ch8Speed->Period(20000000);
	ch8Speed->Duty(  1000000);
	ch8Speed->Polarity(1);
	ch8Speed->Run();
	
	//CHANGE DC
	usleep(5000000);
	ch1Speed->Duty(  1000000);
	ch2Speed->Duty(  1000000);
	ch3Speed->Duty(  1000000);
	ch4Speed->Duty(  1000000);
	ch5Speed->Duty(  1000000);
	ch6Speed->Duty(  1000000);
	ch7Speed->Duty(  1000000);
	ch8Speed->Duty(  1000000);
	
	//STOP
	usleep(10000000);
	ch1Speed->Stop();
	ch2Speed->Stop();
	ch3Speed->Stop();
	ch4Speed->Stop();
	ch5Speed->Stop();
	ch6Speed->Stop();
	ch7Speed->Stop();
	ch8Speed->Stop();

	return 0;

}


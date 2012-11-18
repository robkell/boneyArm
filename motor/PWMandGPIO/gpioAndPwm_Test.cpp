#include "cPWM.h"
#include "Beagle_GPIO.hh"
#include <iostream>
#include <unistd.h>
#include <string>
using namespace std;

int main()
{
	string ch1, ch2, ch3, ch4, ch5, ch6 , ch7, ch8;
	ch1 = "ehrpwm.0:0";
	ch2 = "ehrpwm.0:1";
	ch3 = "ehrpwm.2:0";
	ch4 = "ehrpwm.2:1";
	ch5 = "ecap.2";
	ch6 = "ecap.0";
	ch7 = "ehrpwm.1:0";
	ch8 = "ehrpwm.1:1";
	
	cPWM::cPWM ch1Speed(ch1);
	cPWM::cPWM ch2Speed(ch2);
	cPWM::cPWM ch3Speed(ch3);
	cPWM::cPWM ch4Speed(ch4);
	cPWM::cPWM ch5Speed(ch5);
	cPWM::cPWM ch6Speed(ch6);
	cPWM::cPWM ch7Speed(ch7);
	cPWM::cPWM ch8Speed(ch8);
	Beagle_GPIO	gpio;

	//CONFIG DIRECTION PINS
        
	gpio.configurePin( Beagle_GPIO::P8_26, Beagle_GPIO::kOUTPUT );
        gpio.configurePin( Beagle_GPIO::P8_25, Beagle_GPIO::kOUTPUT );
        gpio.configurePin( Beagle_GPIO::P8_24, Beagle_GPIO::kOUTPUT );
        gpio.configurePin( Beagle_GPIO::P8_23, Beagle_GPIO::kOUTPUT );
        gpio.configurePin( Beagle_GPIO::P8_22, Beagle_GPIO::kOUTPUT );
        gpio.configurePin( Beagle_GPIO::P8_17, Beagle_GPIO::kOUTPUT );
        gpio.configurePin( Beagle_GPIO::P8_18, Beagle_GPIO::kOUTPUT );
        gpio.configurePin( Beagle_GPIO::P8_20, Beagle_GPIO::kOUTPUT );
	gpio.enablePinInterrupts( Beagle_GPIO::P8_26, false );
	gpio.enablePinInterrupts( Beagle_GPIO::P8_25, false );
        gpio.enablePinInterrupts( Beagle_GPIO::P8_24, false );
        gpio.enablePinInterrupts( Beagle_GPIO::P8_23, false );
        gpio.enablePinInterrupts( Beagle_GPIO::P8_22, false );
        gpio.enablePinInterrupts( Beagle_GPIO::P8_17, false );
        gpio.enablePinInterrupts( Beagle_GPIO::P8_18, false );
        gpio.enablePinInterrupts( Beagle_GPIO::P8_20, false );
	
	//SET ALL DIR BITS LOW
	gpio.writePin( Beagle_GPIO::P8_26, 0 );
	gpio.writePin( Beagle_GPIO::P8_25, 0 );
	gpio.writePin( Beagle_GPIO::P8_24, 0 );
	gpio.writePin( Beagle_GPIO::P8_23, 0 );
	gpio.writePin( Beagle_GPIO::P8_22, 0 );
	gpio.writePin( Beagle_GPIO::P8_17, 0 );
	gpio.writePin( Beagle_GPIO::P8_18, 0 );
	gpio.writePin( Beagle_GPIO::P8_20, 0 );

/*	ch1Speed = new cPWM::cPWM(ch1);
	ch2Speed = new cPWM::cPWM(ch2);
	ch3Speed = new cPWM::cPWM(ch3);
	ch4Speed = new cPWM::cPWM(ch4);
	ch5Speed = new cPWM::cPWM(ch5);
	ch6Speed = new cPWM::cPWM(ch6);
	ch7Speed = new cPWM::cPWM(ch7);
	ch8Speed = new cPWM::cPWM(ch8);
*/	
	//RUN CH1
	ch1Speed.Request(1);
	ch1Speed.Period(20000000);
	ch1Speed.Duty(1000000);
	ch1Speed.Polarity(1);
	ch1Speed.Run();
	//RUN CH2
	ch2Speed.Request(1);
	ch2Speed.Period(20000000);
	ch2Speed.Duty(  1000000);
	ch2Speed.Polarity(1);
	ch2Speed.Run();
	//RUN CH3
	ch3Speed.Request(1);
	ch3Speed.Period(20000000);
	ch3Speed.Duty(  1000000);
	ch3Speed.Polarity(1);
	ch3Speed.Run();
	//RUN CH4
	ch4Speed.Request(1);
	ch4Speed.Period(20000000);
	ch4Speed.Duty(  1000000);
	ch4Speed.Polarity(1);
	ch4Speed.Run();
	//RUN CH5
	ch5Speed.Request(1);
	ch5Speed.Period(20000000);
	ch5Speed.Duty(  1000000);
	ch5Speed.Polarity(1);
	ch5Speed.Run();
	//RUN CH6
	ch6Speed.Request(1);
	ch6Speed.Period(20000000);
	ch6Speed.Duty(  1000000);
	ch6Speed.Polarity(1);
	ch6Speed.Run();
	//RUN CH7
	ch7Speed.Request(1);
	ch7Speed.Period(20000000);
	ch7Speed.Duty(  1000000);
	ch7Speed.Polarity(1);
	ch7Speed.Run();
	//RUN CH8
	ch8Speed.Request(1);
	ch8Speed.Period(20000000);
	ch8Speed.Duty(  1000000);
	ch8Speed.Polarity(1);
	ch8Speed.Run();
	
	//CHANGE DC
	usleep(5000000);
	ch1Speed.Duty(  1000000);
	ch2Speed.Duty(  1000000);
	ch3Speed.Duty(  1000000);
	ch4Speed.Duty(  1000000);
	ch5Speed.Duty(  1000000);
	ch6Speed.Duty(  1000000);
	ch7Speed.Duty(  1000000);
	ch8Speed.Duty(  1000000);

	//CHANGE DIRECTION
	//SET ALL DIR BITS HIGH
	usleep(5000000);	
	gpio.writePin( Beagle_GPIO::P8_26, 1 );
	gpio.writePin( Beagle_GPIO::P8_25, 1 );
	gpio.writePin( Beagle_GPIO::P8_24, 1 );
	gpio.writePin( Beagle_GPIO::P8_23, 1 );
	gpio.writePin( Beagle_GPIO::P8_22, 1 );
	gpio.writePin( Beagle_GPIO::P8_17, 1 );
	gpio.writePin( Beagle_GPIO::P8_18, 1 );
	gpio.writePin( Beagle_GPIO::P8_20, 1 );

	//STOP
	usleep(5000000);
	ch1Speed.Stop();
	ch2Speed.Stop();
	ch3Speed.Stop();
	ch4Speed.Stop();
	ch5Speed.Stop();
	ch6Speed.Stop();
	ch7Speed.Stop();
	ch8Speed.Stop();

	return 0;

}


// $Id$
/**
 * @file example.cpp
 * Example implementation of the Simple C++ class wrapper for beaglebone PWM eHRPWM interface
 *
 * @author claus
 *  Created on: Jun 13, 2012
 *      Author: claus http://quadrotordiaries.blogspot.com
 *
 */
// $Log$

///  Example implementation of the Simple C++ class wrapper for beaglebone PWM eHRPWM interface

#include "cPWM.h"
#include <iostream>
#include <unistd.h>
#include <string>
using namespace std;

int main()
{
	cout << "Hello Beagle!" << endl;

	string s1;
	s1 = "ehrpwm.2:1";
	cPWM::cPWM a(s1);
//	a = new cPWM::cPWM(s1);

	a.Request(1);
	a.Period(20000000);
	a.Duty(  10000000);
	a.Polarity(0);
	a.Run();
	usleep(1000000);	
	a.Duty(   5000000);
	usleep(1000000);
	a.Stop();

	return 0;

}


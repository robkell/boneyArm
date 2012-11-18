// $Id$
/**
 * @file cPWM.h
 * Simple C++ class wrapper for beaglebone PWM eHRPWM interface header file
 *
 * @author claus
 *  Created on: Jun 13, 2012
 *      Author: claus http://quadrotordiaries.blogspot.com
 *
 */
// $Log$

#ifndef CPWM_H_
#define CPWM_H_

#include <fstream>
#include <string>

namespace cPWM {

class cPWM {
private:
	std::string id;
	int duty;
	int period;
	int polarity;
	int run;
	int request;

	#define SYSFS_PWM_PREFIX "/sys/class/pwm/"
	#define SYSFS_PWM_DUTY "duty_ns"
	#define SYSFS_PWM_PERIOD "period_ns"
	#define SYSFS_PWM_POLARITY "polarity"
	#define SYSFS_PWM_RUN "run"
	#define SYSFS_PWM_REQUEST "request"

	std::ofstream sysfsfid_request;
	std::ofstream sysfsfid_duty;
	std::ofstream sysfsfid_period;
	std::ofstream sysfsfid_polarity;
	std::ofstream sysfsfid_run;

public:
	cPWM(std::string id);
	virtual ~cPWM();

	int Request(int d);
	int Duty(int d);
	int Period(int d);
	int Polarity(int d);
	int Run();
	int Stop();
};

} /* namespace cPWM */
#endif /* CPWM_H_ */

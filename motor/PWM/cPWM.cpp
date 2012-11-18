#include "cPWM.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

//using namespace std;

namespace cPWM {


cPWM::cPWM(std::string id)
{
	std::cout << "called cPWM constructor" << std::endl;
	cPWM::id = id;

	std::stringstream sysfsfile_duty;
	std::stringstream sysfsfile_period;
	std::stringstream sysfsfile_polarity;
	std::stringstream sysfsfile_run;
	std::stringstream sysfsfile_request;

	sysfsfile_duty << SYSFS_PWM_PREFIX << id << "/" << SYSFS_PWM_DUTY;
	sysfsfile_period << SYSFS_PWM_PREFIX << id << "/" << SYSFS_PWM_PERIOD;
	sysfsfile_polarity << SYSFS_PWM_PREFIX << id << "/" << SYSFS_PWM_POLARITY;
	sysfsfile_run << SYSFS_PWM_PREFIX << id << "/" << SYSFS_PWM_RUN;
	sysfsfile_request << SYSFS_PWM_PREFIX << id << "/" << SYSFS_PWM_REQUEST;

	std::cout << "new PWM with id " << id << std::endl;
	std::cout << "using Duty file " << sysfsfile_duty.str() << std::endl;
	std::cout << "using Period file " << sysfsfile_period.str() << std::endl;
	std::cout << "using Polarity file " << sysfsfile_polarity.str() << std::endl;
	std::cout << "using Run file " << sysfsfile_run.str() << std::endl;
	std::cout << "using Request file " << sysfsfile_request.str() << std::endl;

	sysfsfid_duty.open(sysfsfile_duty.str().c_str());
	sysfsfid_period.open(sysfsfile_period.str().c_str());
	sysfsfid_polarity.open(sysfsfile_polarity.str().c_str());
	sysfsfid_run.open(sysfsfile_run.str().c_str());
	sysfsfid_request.open(sysfsfile_request.str().c_str());

}

int cPWM::Request(int d)
{
		std::cout << "PWM "<< id << "request set to " << d << std::endl;
		cPWM::request = d;
		sysfsfid_request << d << std::endl;
		return 1;
}

int cPWM::Duty(int d)
{
		std::cout << "PWM "<< id << "duty cycle set to " << d << std::endl;
		cPWM::duty = d;
		sysfsfid_duty << d << std::endl;
		return 1;
}

int cPWM::Period(int d)
{
		std::cout << "PWM "<< id << ", period set to " << d << std::endl;
		cPWM::period = d;
		sysfsfid_period << d << std::endl;
		return 1;
}

int cPWM::Polarity(int d)
{
		std::cout << "PWM "<< id << ", polarity set to " << d << std::endl;
		cPWM::polarity = d;
		sysfsfid_polarity << d << std::endl;
		return 1;
}
int cPWM::Run()
{
	std::cout << "PWM "<< id << " started" << std::endl;
	sysfsfid_run << "1" << std::endl;
	cPWM::run = 1;
	return 1;
}

int cPWM::Stop()
{
	std::cout << "PWM "<< id << " stopped" << std::endl;
	sysfsfid_run << "0" << std::endl;
	cPWM::run = 0;
	return 1;
}

/**
 * cPWM Destructor, stops the PWMss
 *
 */
cPWM::~cPWM()
{
	std::cout << "PWM "<< id << " stopped" << std::endl;
	sysfsfid_run << "0" << std::endl;
	std::cout << "called cPWM destructor of cPWM " << id << std::endl;
}

} /* namespace cPWM */

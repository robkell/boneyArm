#include "gpio.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>


//using namespace std;

namespace gpio {


const int gpio::Pin_Bank[] = 
{
        -1, -1,  1,  1,  1,     // P8_1  -> P8_5
         1,  2,  2,  2,  2,     // P8_6  -> P8_10
         1,  1,  0,  0,  1,     // P8_11 -> P8_15
         1,  0,  2,  0,  1,     // P8_16 -> P8_20
         1,  1,  1,  1,  1,     // P8_21 -> P8_25
         1,  2,  2,  2,  2,     // P8_26 -> P8_30
         0,  0,  0,  2,  0,     // P8_31 -> P9_35
         2,  2,  2,  2,  2,     // P8_36 -> P8_40
         2,  2,  2,  2,  2,     // P8_41 -> P8_45
         2,                     // P8_46
        -1, -1, -1, -1, -1,     // P9_1  -> P9_5
        -1, -1, -1, -1, -1,     // P9_6  -> P9_10
         0,  1,  0,  1,  1,     // P9_11 -> P9_15
         1,  0,  0,  0,  0,     // P9_16 -> P9_20
         0,  0,  1,  0,  3,     // P9_21 -> P9_25
         0,  3,  3,  3,  3,     // P9_26 -> P9_30
         3, -1, -1, -1, -1,     // P9_31 -> P9_35
        -1, -1, -1, -1, -1,     // P9_36 -> P9_40
         0,  0, -1, -1, -1,     // P9_41 -> P9_45
        -1                      // P9_46
};

const int gpio::Pin_Id[] = 
{
        -1, -1,  6,  7,  2,     // P8_1  -> P8_5
         3,  2,  3,  5,  4,     // P8_6  -> P8_10
        13, 12, 23, 26, 15,     // P8_11 -> P8_15
        14, 27,  1, 22, 31,     // P8_16 -> P8_20
        30,  5,  4,  1,  0,     // P8_21 -> P8_25
        29, 22, 24, 23, 25,     // P8_26 -> P8_30
        10, 11,  9, 17,  8,     // P8_31 -> P9_35
        16, 14, 15, 12, 13,     // P8_36 -> P8_40
        10, 11,  8,  9,  6,     // P8_41 -> P8_45
         7,                     // P8_46
        -1, -1, -1, -1, -1,     // P9_1  -> P9_5
        -1, -1, -1, -1, -1,     // P9_6  -> P9_10
        30, 28, 31, 18, 16,     // P9_11 -> P9_15
        19,  5,  4, 13, 12,     // P9_16 -> P9_20
         3,  2, 17, 15, 21,     // P9_21 -> P9_25
        14, 19, 17, 15, 16,     // P9_26 -> P9_30
        14, -1, -1, -1, -1,     // P9_31 -> P9_35
        -1, -1, -1, -1, -1,     // P9_36 -> P9_40
        20,  7, -1, -1, -1,     // P9_41 -> P9_45
        -1                      // P9_46
};



gpio::gpio( int i )
{
	std::cout << "called gpio constructor" << std::endl;
	gpio::id = i;
	gpio::num = (Pin_Bank[i]*32)+Pin_Id[i];
	std::cout << "Gpio number" << num <<std::endl; 
	std::stringstream sysfsfile_direction;
	std::stringstream sysfsfile_edge;
	std::stringstream sysfsfile_value;
	std::stringstream sysfsfile_export;
	std::stringstream sysfsfile_unexport;

	sysfsfile_direction << SYSFS_GPIO_PREFIX << "gpio" << num << "/" << SYSFS_GPIO_DIRECTION;
	sysfsfile_edge << SYSFS_GPIO_PREFIX << "gpio" << num << "/" << SYSFS_GPIO_EDGE;
	sysfsfile_value << SYSFS_GPIO_PREFIX << "gpio" << num << "/" << SYSFS_GPIO_VALUE;
	sysfsfile_export << SYSFS_GPIO_PREFIX << "/" << SYSFS_GPIO_EXPORT;
	sysfsfile_unexport << SYSFS_GPIO_PREFIX << "/" << SYSFS_GPIO_UNEXPORT;

	std::cout << "new gpio with id: " << i << ", number: " << num << std::endl;

	sysfsfd_export.open(sysfsfile_export.str().c_str());
	sysfsfd_unexport.open(sysfsfile_unexport.str().c_str());
	
	sysfsfd_export << i << std::endl;
	
	sysfsfd_direction.open(sysfsfile_direction.str().c_str());
	sysfsfd_edge.open(sysfsfile_edge.str().c_str());
	sysfsfd_value.open(sysfsfile_value.str().c_str());
	
	

}

int gpio::direction(std::string d)
{
		std::cout << "gpio "<< id << "direction set to " << d << std::endl;
		gpio::Direction = d;
		sysfsfd_direction << d << std::endl;
		return 1;
}

int gpio::edge(std::string d)
{
		std::cout << "gpio "<< id << "edge " << d << std::endl;
		gpio::Edge = d;
		sysfsfd_edge << d << std::endl;
		return 1;
}

int gpio::write(int d)
{
		std::cout << "PWM "<< id << ", set to " << d << std::endl;
		gpio::Value = d;
		sysfsfd_value << d << std::endl;
		return 1;
}

int gpio::read()
{
		int d;
		sysfsfd_value.seekg(0, std::ios::beg);
		sysfsfd_value>>d;		
		std::cout << "PWM "<< id << ", value is " << d << std::endl;
		gpio::Value = d;
		return d;
}


/**
 * cPWM Destructor, stops the PWMss
 *
 */
gpio::~gpio()
{
	std::cout << "gpio "<< id << " unexported" << std::endl;
	sysfsfd_unexport << id << std::endl;
	std::cout << "called gpio destructor of" << id << std::endl;
}

} /* namespace cPWM */

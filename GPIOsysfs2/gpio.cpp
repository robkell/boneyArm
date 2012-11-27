#include "gpio.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/queue.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/epoll.h>
using namespace std;


int intWrite(int fd, int i)
{
	//cout << "writing i: " << i << endl;
	char str[4];
	char* wstr[sizeof(str)];
	int j, base=10, k=0, quotient=i;

	for (j=0; j<sizeof(str); j++) 
	{
		wstr[j] = &str[j];
	}
	do {
		const int tmp = quotient / base;
		*wstr[k] =  "0123456789abcdef"[ quotient - (tmp*base) ];
		//cout << "added char: " << *wstr[k] << endl;
		//cout << "quotient = " << tmp << endl;
		quotient = tmp;
		k=k+1;
	}while(quotient>0);
	*wstr[k]='\0';
	char buf[sizeof(str)];
	for(int l=0; l<sizeof(str); l++){
		buf[l]=str[k-(l+1)];
	}
	buf[k]='\0';
	int written = write(fd, buf, strlen(buf) );
	if(written<0){
	 	printf("Cannot export: %s\n", strerror( errno ));
	}

	return written;
}

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
	
	std::stringstream sysfsfile_direction;
	std::stringstream sysfsfile_edge;
	std::stringstream sysfsfile_value;
	std::stringstream sysfsfile_export;

	sysfsfile_direction << SYSFS_GPIO_PREFIX << "gpio" << num << "/" << SYSFS_GPIO_DIRECTION;
	sysfsfile_edge << SYSFS_GPIO_PREFIX << "gpio" << num << "/" << SYSFS_GPIO_EDGE;
	sysfsfile_value << SYSFS_GPIO_PREFIX << "gpio" << num << "/" << SYSFS_GPIO_VALUE;
	sysfsfile_export << SYSFS_GPIO_PREFIX << SYSFS_GPIO_EXPORT;

	std::cout << "new gpio with id: " << i << ", number: " << num << std::endl;
	//std::cout << "export fd: " << sysfsfile_export.str().c_str() << endl;
	
	sysfsfd_export = open(sysfsfile_export.str().c_str(), O_WRONLY);

	sysfsfd_export = open(sysfsfile_export.str().c_str(), O_WRONLY);
	if(sysfsfd_export<0){
	 	printf("Cannot open GPIO to export it: %s\n", strerror( errno ));
	}
	intWrite(sysfsfd_export, gpio::num);//export gpio
	close(sysfsfd_export);

	//std::cout << "direction fd: " << sysfsfile_direction.str().c_str() << endl;
	sysfsfd_direction = open(sysfsfile_direction.str().c_str(),  O_WRONLY);
	if(sysfsfd_direction<0){
	 	printf("Cannot open GPIO direction: %s\n", strerror( errno ));
	}

	sysfsfd_edge = open(sysfsfile_edge.str().c_str(),  O_WRONLY);
	if(sysfsfd_edge<0){
	 	printf("Cannot open GPIO edge: %s\n", strerror( errno ));
	}

	sysfsfd_value = open(sysfsfile_value.str().c_str(),  O_WRONLY);
	if(sysfsfd_value<0){
	 	printf("Cannot open GPIO value: %s\n", strerror( errno ));
	}

}

int gpio::direction(std::string d)
{
		std::cout << "gpio"<< gpio::num << " direction set to " << d << std::endl;
		gpio::Direction = d;
		int written = write(sysfsfd_direction, d.c_str(), strlen(d.c_str()) );
		if(written<0){
		 	printf("Cannot set direction: %s\n", strerror( errno ));
			return -1;
		}else{
			return 1;
		}
}

int gpio::edge(std::string d)
{
		std::cout << "gpio"<< gpio::num << " edge " << d << std::endl;
		gpio::Edge = d;
		int written = write(sysfsfd_edge, d.c_str(), strlen(d.c_str()) );
		if(written<0){
		 	printf("Cannot set edge: %s\n", strerror( errno ));
			return -1;
		}else{
			return 1;
		}
}

int gpio::set(std::string d)
{
		std::cout << "gpio"<< gpio::num << ", set to " << d << std::endl;
		gpio::Value = d;
		int written = write(sysfsfd_value, d.c_str(), strlen(d.c_str()) );
		if(written<0){
		 	printf("Cannot set value: %s\n", strerror( errno ));
			return -1;
		}else{
			return 1;
		}
}

int gpio::get()
{
		int d, m = 0;
                char buf[64];
                m = lseek(sysfsfd_value, 0, SEEK_SET);
                m = read(sysfsfd_value, &buf, 63);
		d = atoi(buf);
		std::cout << "gpio"<< gpio::num << ", value is " << d << std::endl;
		return d;
}


/**
 * cPWM Destructor, stops the PWMss
 *
 */
gpio::~gpio()
{
	std::stringstream sysfsfile_unexport;
	sysfsfile_unexport << SYSFS_GPIO_PREFIX << SYSFS_GPIO_UNEXPORT;

	std::cout << "gpio"<< gpio::num << " unexported" << std::endl;
	close(sysfsfd_direction);
	close(sysfsfd_edge);
	close(sysfsfd_value);
	sysfsfd_unexport = open(sysfsfile_unexport.str().c_str(), O_WRONLY);
	if(sysfsfd_unexport<0){
	 	printf("Cannot open GPIO to unexport it: %s\n", strerror( errno ));
	}
	intWrite(sysfsfd_unexport, gpio::num);//unexport gpio
	close(sysfsfd_unexport);
	std::cout << "called gpio destructor of" << id << std::endl;
}

} /* namespace cPWM */

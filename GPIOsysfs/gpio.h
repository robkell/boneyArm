#ifndef GPIO_H_
#define GPIO_H_

#include <fstream>
#include <string>

namespace gpio {

class gpio {

private:
	unsigned short id, i;
	std::string Direction;
	std::string Edge;
	int Value;
	int num;

	#define SYSFS_GPIO_PREFIX "/sys/class/gpio/"
	#define SYSFS_GPIO_DIRECTION "direction"
	#define SYSFS_GPIO_EDGE "edge"
	#define SYSFS_GPIO_VALUE "value"
	#define SYSFS_GPIO_EXPORT "export"
	#define SYSFS_GPIO_UNEXPORT "unexport"
	
	std::ofstream sysfsfd_direction;
	std::ofstream sysfsfd_edge;
	std::fstream sysfsfd_value;
	std::ofstream sysfsfd_export;
	std::ofstream sysfsfd_unexport;

public:
	static const int Pin_Bank[];
	static const int Pin_Id[];

	gpio( int );
	virtual ~gpio();

	int direction( std::string d);
	int edge( std::string d);
	int write(int d);
	int read();
};

} /* namespace gpio */
#endif /* GPIO_H_ */
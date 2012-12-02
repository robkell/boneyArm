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
	std::string Value;
	int num;

	#define SYSFS_GPIO_PREFIX "/sys/class/gpio/"
	#define SYSFS_GPIO_DIRECTION "direction"
	#define SYSFS_GPIO_EDGE "edge"
	#define SYSFS_GPIO_VALUE "value"
	#define SYSFS_GPIO_EXPORT "export"
	#define SYSFS_GPIO_UNEXPORT "unexport"
	#define HIGH	"1"
	#define LOW	"0"

	int sysfsfd_direction;
	int sysfsfd_edge;
	int sysfsfd_value;
	int sysfsfd_export;
	int sysfsfd_unexport;

public:
	static const int Pin_Bank[];
	static const int Pin_Id[];

	gpio( int );
	virtual ~gpio();

	int direction( std::string d);
	int edge( std::string d);
	int set(std::string d);
	int get();
	int retfd(){return sysfsfd_value;};
	int retVal(){return Value;};
};

} /* namespace gpio */
#endif /* GPIO_H_ */


#include "Beagle_GPIO.hh"

#include <iostream>

Beagle_GPIO	gpio;

int main()
{
	GPIO_PRINT( "====================" );
	GPIO_PRINT( "BeagleBone GPIO Test" );
	GPIO_PRINT( "====================" );

	GPIO_PRINT( "Configuring Pin P8_46 as Output" );
	gpio.configurePin( Beagle_GPIO::P8_46, Beagle_GPIO::kINPUT );
	gpio.enablePinInterrupts( Beagle_GPIO::P8_46, true );
	int read;
	while (1)
	{
		GPIO_PRINT( "READING P8_46" );
		read = gpio.readPin( Beagle_GPIO::P8_46 );
		GPIO_PRINT( "READ P8_46: %i", read );
	}
	return 0;
}

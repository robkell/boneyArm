#!/bin/bash

BASEDIR=$(dirname $0)
source $BASEDIR/directories.sh

CHANNEL=$1
FREQ=$2
DUTY=$3


#CONFIG  GPIOS
function configgpio {
        echo out > $1direction
        echo 1 > $1value
}
function checkgpio {
	if [ ! -d $1 ]; then
        	echo $2 > /sys/class/gpio/export
	fi
}


case $CHANNEL in
    6)  checkgpio $MOTOR6_PWM_GPIO $MOTOR6_PWM_GPIO_NO;
	configgpio $MOTOR6_PWM_GPIO;
	checkgpio $MOTOR6_DIR $MOTOR6_DIR_GPIO;
	configgpio $MOTOR6_DIR;;
    7)  checkgpio $MOTOR7_PWM_GPIO $MOTOR7_PWM_GPIO_NO;
	checkgpio $MOTOR7_DIR $MOTOR7_DIR_GPIO
	configgpio $MOTOR7_DIR;
	configgpio $MOTOR7_PWM_GPIO;;
    8)  checkgpio $MOTOR8_PWM_GPIO $MOTOR8_PWM_GPIO_NO;
	checkgpio $MOTOR8_DIR $MOTOR8_DIR_GPIO
	configgpio $MOTOR8_DIR;
	configgpio $MOTOR8_PWM_GPIO;;
esac 

#!/bin/bash

source $(dirname $0)/directories.sh

CHANNEL=$1
FREQ=$2
DUTY=$3


#CONFIG  GPIOS
function configgpio {
        echo out > $1direction
        echo 0 > $1value
}
function configsense {
        echo in > $1direction
        echo both > $1edge
}
function checkgpio {
	if [ ! -d $1 ]; then
        	echo $2 > /sys/class/gpio/export
	fi
}


case $CHANNEL in
    1) echo 1 >  ${MOTOR1_PWM}request; echo $FREQ > ${MOTOR1_PWM}period_freq; 
	echo $DUTY > ${MOTOR1_PWM}duty_percent; echo 0 > ${MOTOR1_PWM}polarity;
	checkgpio $MOTOR1_DIR $MOTOR1_DIR_GPIO;
	configgpio $MOTOR1_DIR;
	checkgpio $MOTOR1_SENSE1 $MOTOR1_SENSE1_GPIO;
	configsense $MOTOR1_SENSE1;
	checkgpio $MOTOR1_SENSE2 $MOTOR1_SENSE2_GPIO;
	configsense $MOTOR1_SENSE2;;
    2) echo 1 >  ${MOTOR2_PWM}request; echo $FREQ > ${MOTOR2_PWM}period_freq; 
	echo $DUTY > ${MOTOR2_PWM}duty_percent; echo 0 > ${MOTOR2_PWM}polarity;
	checkgpio $MOTOR2_DIR $MOTOR2_DIR_GPIO;
	configgpio $MOTOR2_DIR;
	checkgpio $MOTOR2_SENSE1 $MOTOR2_SENSE1_GPIO;
	configsense $MOTOR2_SENSE1;
	checkgpio $MOTOR2_SENSE2 $MOTOR2_SENSE2_GPIO;
	configsense $MOTOR2_SENSE2;;
    3) echo 1 >  ${MOTOR3_PWM}request; echo $FREQ > ${MOTOR3_PWM}period_freq; 
	echo $DUTY > ${MOTOR3_PWM}duty_percent; echo 0 > ${MOTOR3_PWM}polarity;
	checkgpio $MOTOR3_DIR $MOTOR3_DIR_GPIO;
	configgpio $MOTOR3_DIR;
	checkgpio $MOTOR3_SENSE1 $MOTOR3_SENSE1_GPIO;
	configsense $MOTOR3_SENSE1;
	checkgpio $MOTOR3_SENSE2 $MOTOR3_SENSE2_GPIO;
	configsense $MOTOR3_SENSE2;;
    4) echo 1 >  ${MOTOR4_PWM}request; echo $FREQ > ${MOTOR4_PWM}period_freq; 
	echo $DUTY > ${MOTOR4_PWM}duty_percent; echo 0 > ${MOTOR4_PWM}polarity;
	checkgpio $MOTOR4_DIR $MOTOR4_DIR_GPIO;
	configgpio $MOTOR4_DIR;
	checkgpio $MOTOR4_SENSE1 $MOTOR4_SENSE1_GPIO;
	configsense $MOTOR4_SENSE1;
	checkgpio $MOTOR4_SENSE2 $MOTOR4_SENSE2_GPIO;
	configsense $MOTOR4_SENSE2;;
    5) echo 1 >  ${MOTOR5_PWM}request; echo $FREQ > ${MOTOR5_PWM}period_freq; 
	echo $DUTY > ${MOTOR5_PWM}duty_percent; echo 0 > ${MOTOR5_PWM}polarity;
	checkgpio $MOTOR5_DIR $MOTOR5_DIR_GPIO;
	configgpio $MOTOR5_DIR;
   	checkgpio $MOTOR5_SENSE1 $MOTOR5_SENSE1_GPIO;
	configsense $MOTOR5_SENSE1;
	checkgpio $MOTOR5_SENSE2 $MOTOR5_SENSE2_GPIO;
	configsense $MOTOR5_SENSE2;;
    6) echo 1 >  ${MOTOR6_PWM}request; echo $FREQ > ${MOTOR6_PWM}period_freq; 
	echo $DUTY > ${MOTOR6_PWM}duty_percent; echo 0 > ${MOTOR6_PWM}polarity;
	checkgpio $MOTOR6_DIR $MOTOR6_DIR_GPIO;
	configgpio $MOTOR6_DIR;
	checkgpio $MOTOR6_SENSE1 $MOTOR6_SENSE1_GPIO;
	configsense $MOTOR6_SENSE1;
	checkgpio $MOTOR6_SENSE2 $MOTOR6_SENSE2_GPIO;
	configsense $MOTOR6_SENSE2;;
    7) echo 1 >  ${MOTOR7_PWM}request; echo $FREQ > ${MOTOR7_PWM}period_freq; 
	echo $DUTY > ${MOTOR7_PWM}duty_percent; echo 0 > ${MOTOR7_PWM}polarity;
	checkgpio $MOTOR7_DIR $MOTOR7_DIR_GPIO;
	configgpio $MOTOR7_DIR;
	checkgpio $MOTOR7_SENSE1 $MOTOR7_SENSE1_GPIO;
	configsense $MOTOR7_SENSE1;
	checkgpio $MOTOR7_SENSE2 $MOTOR7_SENSE2_GPIO;
	configsense $MOTOR7_SENSE2;;
    8) echo 1 >  ${MOTOR8_PWM}request; echo $FREQ > ${MOTOR8_PWM}period_freq; 
	echo $DUTY > ${MOTOR8_PWM}duty_percent; echo 0 > ${MOTOR8_PWM}polarity;
	checkgpio $MOTOR8_DIR $MOTOR8_DIR_GPIO;
	configgpio $MOTOR8_DIR;
	checkgpio $MOTOR8_SENSE1 $MOTOR8_SENSE1_GPIO;
	configsense $MOTOR8_SENSE1;
	checkgpio $MOTOR8_SENSE2 $MOTOR8_SENSE2_GPIO;
	configsense $MOTOR8_SENSE2;;
esac 

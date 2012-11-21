#!/bin/bash

source $(dirname $0)/directories.sh

CHANNEL=$1

case $CHANNEL in
    1) echo 0 >  ${MOTOR1_PWM}run;;
    2) echo 0 >  ${MOTOR2_PWM}run;;
    3) echo 0 >  ${MOTOR3_PWM}run;;
    4) echo 0 >  ${MOTOR4_PWM}run;;
    5) echo 0 >  ${MOTOR5_PWM}run;;
    6) echo 0 >  ${MOTOR6_PWM}run;;
    7) echo 0 >  ${MOTOR7_PWM}run;;
    8) echo 0 >  ${MOTOR8_PWM}run;;
esac 

#!/bin/bash

source $(dirname $0)/directories.sh

CHANNEL=$1

case $CHANNEL in
    1) echo 1 >  ${MOTOR1_PWM}run;;
    2) echo 1 >  ${MOTOR2_PWM}run;;
    3) echo 1 >  ${MOTOR3_PWM}run;;
    4) echo 1 >  ${MOTOR4_PWM}run;;
    5) echo 1 >  ${MOTOR5_PWM}run;;
    6) echo 1 >  ${MOTOR6_PWM}run;;
    7) echo 1 >  ${MOTOR7_PWM}run;;
    8) echo 1 >  ${MOTOR8_PWM}run;;
esac 

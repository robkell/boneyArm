#!/bin/bash

BASEDIR=$(dirname $0)
source $BASEDIR/directories.sh

CHANNEL=$1

case $CHANNEL in
    1) echo 0 >  ${MOTOR1_PWM}request;;
    2) echo 0 >  ${MOTOR2_PWM}request;;
    3) echo 0 >  ${MOTOR3_PWM}request;;
    4) echo 0 >  ${MOTOR4_PWM}request;;
    5) echo 0 >  ${MOTOR5_PWM}request;;
    6) echo 0 >  ${MOTOR6_PWM}request;;
    7) echo 0 >  ${MOTOR7_PWM}request;;
    8) echo 0 >  ${MOTOR8_PWM}request;;
esac 

#!/bin/bash

source $(dirname $0)/directories.sh

CHANNEL=$1
FREQ=$2

case $CHANNEL in
    1) echo $FREQ >  ${MOTOR1_PWM}period_freq;;
    2) echo $FREQ >  ${MOTOR2_PWM}period_freq;;
    3) echo $FREQ >  ${MOTOR3_PWM}period_freq;;
    4) echo $FREQ >  ${MOTOR4_PWM}period_freq;;
    5) echo $FREQ >  ${MOTOR5_PWM}period_freq;;
    6) echo $FREQ >  ${MOTOR6_PWM}period_freq;;
    7) echo $FREQ >  ${MOTOR7_PWM}period_freq;;
    8) echo $FREQ >  ${MOTOR8_PWM}period_freq;;
esac 

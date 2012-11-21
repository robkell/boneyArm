#!/bin/bash

source $(dirname $0)/directories.sh

CHANNEL=$1
DUTY=$2

case $CHANNEL in
    1) echo $DUTY >  ${MOTOR1_PWM}duty_percent;;
    2) echo $DUTY >  ${MOTOR2_PWM}duty_percent;;
    3) echo $DUTY >  ${MOTOR3_PWM}duty_percent;;
    4) echo $DUTY >  ${MOTOR4_PWM}duty_percent;;
    5) echo $DUTY >  ${MOTOR5_PWM}duty_percent;;
    6) echo $DUTY >  ${MOTOR6_PWM}duty_percent;;
    7) echo $DUTY >  ${MOTOR7_PWM}duty_percent;;
    8) echo $DUTY >  ${MOTOR8_PWM}duty_percent;;
esac 

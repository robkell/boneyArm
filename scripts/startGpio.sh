#!/bin/bash

source ./directories.sh

CHANNEL=$1

case $CHANNEL in
    6) echo 1 >  ${MOTOR6_PWM_GPIO}value;;
    7) echo 1 >  ${MOTOR7_PWM_GPIO}value;;
    8) echo 1 >  ${MOTOR8_PWM_GPIO}value;;
esac 

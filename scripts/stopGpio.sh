#!/bin/bash

BASEDIR=$(dirname $0)
source $BASEDIR/directories.sh

CHANNEL=$1

case $CHANNEL in
    6) echo 0 >  ${MOTOR6_PWM_GPIO}value;;
    7) echo 0 >  ${MOTOR7_PWM_GPIO}value;;
    8) echo 0 >  ${MOTOR8_PWM_GPIO}value;;
esac 

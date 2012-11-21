#!/bin/bash

source $(dirname $0)/directories.sh

CHANNEL=$1

LEFT=1
RIGHT=0

case $CHANNEL in
    1) GPIO=${MOTOR1_DIR};;
    2) GPIO=${MOTOR2_DIR};;
    3) GPIO=${MOTOR3_DIR};;
    4) GPIO=${MOTOR4_DIR};;
    5) GPIO=${MOTOR5_DIR};;
    6) GPIO=${MOTOR6_DIR};;
    7) GPIO=${MOTOR7_DIR};;
    8) GPIO=${MOTOR8_DIR};;
esac 

DIRECTION=`cat ${GPIO}value`
#echo $DIRECTION

if [ $DIRECTION  -eq $LEFT ]; then
	echo ${RIGHT} > ${GPIO}value
#	echo "LEFT"
else
	echo ${LEFT} > ${GPIO}value
#	echo "RIGHT"
fi

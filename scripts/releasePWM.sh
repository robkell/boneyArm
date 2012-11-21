#!/bin/bash

echo 0 > /sys/class/pwm/ecap.0/request
echo 0 > /sys/class/pwm/ecap.2/request
echo 0 > /sys/class/pwm/ehrpwm.1\:0/request
echo 0 > /sys/class/pwm/ehrpwm.1\:1/request
echo 0 > /sys/class/pwm/ehrpwm.0\:1/request
echo 0 > /sys/class/pwm/ehrpwm.0\:0/request
echo 0 > /sys/class/pwm/ehrpwm.2\:0/request
echo 0 > /sys/class/pwm/ehrpwm.2\:1/request

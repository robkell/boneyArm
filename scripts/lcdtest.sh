#!/bin/bash

BASEDIR=$(dirname $0)
source $BASEDIR/directories.sh

STARTCH=1	#first channel
CHANNELS=6	#last channel + 1
GPIO=6
TOTAL=9

COUNT=$STARTCH
while [ $COUNT -lt $CHANNELS ]; do
	$BASEDIR/setupChannel.sh $COUNT 100 50
	$BASEDIR/startChannel.sh $COUNT 
	let COUNT=COUNT+1
done 

COUNT=$GPIO
while [ $COUNT -lt $TOTAL ]; do
	$BASEDIR/setupGpio.sh $COUNT 
	$BASEDIR/startGpio.sh $COUNT 
	let COUNT=COUNT+1
done 



sleep 2

COUNT=$STARTCH
while [ $COUNT -lt $TOTAL ]; do
	$BASEDIR/changeDirection.sh $COUNT
	echo "change direction of channel "$COUNT 
	sleep 1
	let COUNT=COUNT+1
done 

sleep 2


DUTY=0
while [ $DUTY -lt 110 ]; do
	
	COUNT=$STARTCH	
	while [ $COUNT -lt $CHANNELS ]; do
		$BASEDIR/setDuty.sh $COUNT $DUTY 
		echo "setting channel "$COUNT" to "$DUTY"%"
		sleep 1
		let COUNT=COUNT+1
	done 

	sleep 1
	let DUTY=DUTY+20
done

#COUNT=$STARTCH
#while [ $COUNT -lt $CHANNELS ]; do
#	$BASEDIR/stopChannel.sh $COUNT
#	echo "stopping channel "$COUNT
#	sleep 1
#	let COUNT=COUNT+1
#done 

COUNT=$GPIO
while [ $COUNT -lt $TOTAL ]; do
	$BASEDIR/stopGpio.sh $COUNT 
	echo "stopping channel "$COUNT
	sleep 1
	let COUNT=COUNT+1
done 

COUNT=$STARTCH
while [ $COUNT -lt $CHANNELS ]; do
	$BASEDIR/releaseChannel.sh $COUNT
	echo "releasing channel "$COUNT
	let COUNT=COUNT+1
done 

#$BASEDIR/releasePWM.sh





#!/bin/bash

source ./directories.sh

STARTCH=1	#first channel
CHANNELS=9	#last channel + 1

COUNT=$STARTCH
while [ $COUNT -lt $CHANNELS ]; do
	./setupChannel.sh $COUNT 100 50
	./startChannel.sh $COUNT 
	let COUNT=COUNT+1
done 

sleep 2

COUNT=$STARTCH
while [ $COUNT -lt $CHANNELS ]; do
	./changeDirection.sh $COUNT
	echo "change direction of channel "$COUNT 
	sleep 1
	let COUNT=COUNT+1
done 

sleep 2


DUTY=0
while [ $DUTY -lt 110 ]; do
	
	COUNT=$STARTCH	
	while [ $COUNT -lt $CHANNELS ]; do
		./setDuty.sh $COUNT $DUTY 
		echo "setting channel "$COUNT" to "$DUTY"%"
		sleep 1
		let COUNT=COUNT+1
	done 

	sleep 1
	let DUTY=DUTY+20
done

COUNT=$STARTCH
while [ $COUNT -lt $CHANNELS ]; do
	./stopChannel.sh $COUNT
	echo "stopping channel "$COUNT
	sleep 1
	let COUNT=COUNT+1
done 

COUNT=$STARTCH
while [ $COUNT -lt $CHANNELS ]; do
	./releaseChannel.sh $COUNT
	echo "releasing channel "$COUNT
	let COUNT=COUNT+1
done 

#./releasePWM.sh





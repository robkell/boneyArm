boneyArm: ik.o pid.o ballTracker.o gpio.o cPWM.o
	g++ boneyArm.cpp ./IK/ik.o ./PID/pid.o ./ballTracker/ballTracker.o ./GPIO/gpio.o \
	./PWM/cPWM.o -I. -levent -lopencv_highgui -lopencv_core -lopencv_imgproc -ffast-math -O2 -o boneyArm

ik.o:
	cd ./IK; make ik.o

pid.o:
	cd ./PID; make pid.o

ballTracker.o:
	cd ./ballTracker; make ballTracker.o

gpio.o:
	cd ./GPIO; make gpio.o

cPWM.o:
	cd ./PWM; make cPWM.o

clean:
	rm -rf *.o
	cd ./PWM; make clean
	cd ./GPIO; make clean
	cd ./IK; make clean
	cd ./PID; make clean
	cd ./ballTracker; make clean

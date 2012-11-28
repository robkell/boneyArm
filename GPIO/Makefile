
all: exampleRead exampleWrite gpio.o

exampleRead: gpio.o exampleRead.cpp
	g++ gpio.o exampleRead.cpp -I. -O2 -levent -o exampleRead

exampleWrite: gpio.o exampleWrite.cpp
	g++ gpio.o exampleWrite.cpp -O2 -o exampleWrite

gpio.o: gpio.cpp gpio.h
	g++ -c gpio.cpp gpio.h -O2 -Wall 

clean: 
	rm -rf *.o


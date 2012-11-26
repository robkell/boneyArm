
all: exampleRead exampleWrite gpio.o

exampleRead: gpio.o exampleRead.cpp
	g++ gpio.o exampleRead.cpp -O2 -o exampleRead

exampleWrite: gpio.o exampleWrite.cpp
	g++ gpio.o exampleWrite.cpp -O2 -o exampleWrite

gpio.o: gpio.cpp gpio.h
	g++ -c gpio.cpp gpio.h -O2
 
clean: 
	rm -rf *.o


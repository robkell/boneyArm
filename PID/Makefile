example: pid.o example.cpp
	g++ -o example pid.o example.cpp -O2

pid.o: pid.cpp pid.hpp
	g++ -c pid.cpp pid.hpp -O2
 
clean: 
	rm -rf *.o


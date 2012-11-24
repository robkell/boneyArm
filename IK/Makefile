example: ik.o exampleIK.cpp
	g++ -o example ik.o -O2 -ffast-math -Wall exampleIK.cpp

ik.o: ik.cpp ik.hpp
	g++ -c ik.cpp -O2 -ffast-math -Wall ik.hpp
 
clean: 
	rm -rf *.o


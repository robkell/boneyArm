example: ballTracker.o example.cpp
	g++ -o example ballTracker.o example.cpp -lopencv_highgui \
	-lopencv_core -lopencv_imgproc -ffast-math -O3

ballTracker.o: ballTracker.cpp ballTracker.hpp
	g++ -c ballTracker.cpp ballTracker.hpp -lopencv_highgui \
	-lopencv_core -lopencv_imgproc -ffast-math -O3

clean: 
	rm -rf *.o


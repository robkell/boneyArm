
######################################
######################################

CXX=g++

CFLAGS=-Wall -c -O3

LDFLAGS=-Wall -O3

TARGETS = Beagle_GPIO.o	\
	  Beagle_GPIO_test \

all: $(TARGETS)

Beagle_GPIO.o: Beagle_GPIO.cc Beagle_GPIO.hh
	@echo Compiling $< to $@
	@$(CXX) $(CFLAGS) Beagle_GPIO.cc

Beagle_GPIO_HD44780.o: Beagle_GPIO_HD44780.cc Beagle_GPIO_HD44780.hh
	@echo Compiling $< to $@
	@$(CXX) $(CFLAGS) Beagle_GPIO_HD44780.cc -o $@

clean:
	@rm -rf *~ *.o $(TARGETS) 


######################################
######################################


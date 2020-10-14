CXX = g++
CXXFLAGS = -Wall

mc: main.o Timing.o
	$(CXX) $(CXXFLAGS) -o mc main.o Timing.o

main.o: main.cpp fileHandler.h MedianOfMedians.h MedianQuicksort.h RandomizedSelect.h Timing.h Wirth.h common.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Timing.o: Timing.h

clean :
	-rm *.o mc

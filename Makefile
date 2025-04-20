CXX ?= g++

CXXFLAGS := -c -Wall -ansi -pedantic -std=c++20

all: exe

exe: dvr.o
	$(CXX) -o exe dvr.o


dvr.o: dvr.cpp 
	$(CXX) $(CXXFLAGS) dvr.cpp

clean:
	/bin/rm -f *~ *.o exe dvr.o 

.PHONY: clean

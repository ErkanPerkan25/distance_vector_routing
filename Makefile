CXX ?= g++

CXXFLAGS := -c -Wall -ansi -pedantic -std=c++20

all: exe

exe: main.o
	$(CXX) -o exe main.o


main.o: main.cpp
	$(CC) $(CXXFLAGS) main.cpp


clean:
	/bin/rm -f *~ *.o transmit exe main.o

.PHONY: clean

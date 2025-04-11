CXX ?= g++

CXXFLAGS := -c -Wall -ansi -pedantic -std=c++20

all: exe

exe: main.o Router.o
	$(CXX) -o exe main.o Router.o


main.o: main.cpp 
	$(CXX) $(CXXFLAGS) main.cpp

Router.o: Router.cpp Router.hpp
	$(CXX) $(CXXFLAGS) Router.cpp

clean:
	/bin/rm -f *~ *.o exe main.o Router.o

.PHONY: clean

CXXFLAGS= -std=c++11 -Wall -pedantic -g
CHEADERS = Logger.h
CXXOBJS= Logger.o

main : main.o $(CHEADERS) $(CXXOBJS)
	g++ $(CXXFLAGS) -o main main.o $(CXXOBJS)

%.o : %.cpp  $(CHEADERS)
	g++ $(CXXFLAGS) -c  $<


clean:
	rm -f *.o
	rm -f test main

test: test.o $(CXXOBJS) $(CHEADERS)
	g++ $(CXXFLAGS) -o test test.o $(CXXOBJS)
	./test

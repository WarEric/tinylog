ALL=example

example:example.cc logger.o
	g++ -o example example.cc logger.o
logger.o:logger.h logger.cc
	g++ -c logger.cc -lpthread

clean:
	- rm -f *.o
	- rm -f example

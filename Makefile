#**************************************
# Makefile
#
# Makefile for lang compiler
#
# Author: Phil Howard 
# phil.howard@oit.edu
#
# Date: Jan. 12, 2016
#

COPTS=-Wall -g -c -O0 -std=c++11
OBJS = langlex.o \
	fileopen.o

all: lang

test: testscanner

clean:
	rm -f $(OBJS)
	rm -f *.o
	rm -f langlex.c
	rm -f lang
	rm -f testscanner
	rm -f out.xml
	rm -f out2.xml

.c.o:
	g++ $(COPTS) $? -o $@

.cpp.o:
	g++ $(COPTS) $? -o $@

main.o: main.cpp langlex.c
	g++ $(COPTS) main.cpp -o main.o

testscanner.o: testscanner.cpp langlex.c
	g++ $(COPTS) testscanner.cpp -o testscanner.o

langlex.c: lang.l
	flex -o langlex.c lang.l

langlex.o: langlex.c
	g++ $(COPTS) -Wno-sign-compare $? -o $@

lang: $(OBJS) main.o
	g++ $(OBJS) main.o -o $@

testscanner: $(OBJS) testscanner.o
	g++ $(OBJS) testscanner.o -o $@

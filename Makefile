#**************************************
# Makefile
#
# Makefile for lang compiler
#
# Author: Jacob Locke
#
# Date: Jan. 14, 2021
#

SRC := src
OBJ := obj
INCL := hdr

CC=g++
COPTS=-Wall -g -c -O0 -std=c++11 -I$(INCL) -I./

SRCS := $(wildcard $(SRC)/*.cpp)
OBJS := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))

PROG = lang
TESTPROG = lang_test

all: $(PROG)

test: buildt runt

buildt: $(TESTPROG)

runt:
	xtest/test

clean:
	rm -rf $(OBJ)
	rm -f *.o
	rm -f $(PROG)
	rm -f $(TESTPROG)
	rm -f langlex.c
	rm -f langlex.o
	rm -f langparse.c
	rm -f langparse.h
	rm -f out.xml
	rm -f out2.xml
	rm -f langout.sl
	rm -f langout.slb

$(PROG): $(PROG).o langparse.o langlex.o $(OBJS)
	$(CC) $(OBJS) langlex.o langparse.o $@.o  -o $@

$(TESTPROG): $(TESTPROG).o langparse.o langlex.o $(OBJS)
	$(CC) $(OBJS) langlex.o langparse.o $@.o  -o $@

langlex.c: lang.l langparse.c
	flex -o langlex.c lang.l

langlex.o: langlex.c
	$(CC) $(COPTS) -Wno-sign-compare $? -o $@

langparse.c: lang.y
	bison --defines=langparse.h lang.y -o langparse.c

langparse.o: langparse.c
		$(CC) $(COPTS) $? -o $@

%.o: %.cpp
	$(CC) $(COPTS) $? -o $@

$(OBJ)/%.o: $(SRC)/%.cpp obj
	$(CC) $(COPTS) $< -o $@

obj:
	mkdir -p $(OBJ)

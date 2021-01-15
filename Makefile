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
COPTS=-Wall -g -c -O0 -std=c++11 -I$(INCL)

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
	rm -f out.xml
	rm -f out2.xml

$(PROG): $(PROG).o $(OBJS) langlex.o
	$(CC) $(OBJS) langlex.o $@.o  -o $@

$(TESTPROG): $(TESTPROG).o $(OBJS) langlex.o
	$(CC) $(OBJS) langlex.o $@.o  -o $@

#$(OBJ)/$(PROGS).o: $(PROGS).cpp langlex.o
#	$(CC) $(COPTS) $(PROGS).cpp -o $(OBJ)/$(PROGS).o

#$(OBJ)/$(TESTPROGS).o: $(TESTPROGS).cpp langlex.o
#	$(CC) $(COPTS) $? -o $@

#lang: $(OBJS) $(OBJ)/main.o
#	$(CC) $(OBJS) $(OBJ)/main.o -o $@
#
#$(OBJ)/main.o: main.cpp langlex.c
#	$(CC) $(COPTS) main.cpp -o $(OBJ)/main.o
#
#test_scanner: $(OBJS) $(OBJ)/test_scanner.o
#	$(CC) $(OBJS) $(OBJ)/test_scanner.o -o $@
#
#$(OBJ)/test_scanner.o: test_scanner.cpp langlex.c
#	$(CC) $(COPTS) test_scanner.cpp -o $(OBJ)/test_scanner.o
#
langlex.c: lang.l
	flex -o langlex.c lang.l

langlex.o: langlex.c
	$(CC) $(COPTS) -Wno-sign-compare $? -o $@

%.o: %.cpp
	$(CC) $(COPTS) $? -o $@

$(OBJ)/%.o: $(SRC)/%.cpp obj
	$(CC) $(COPTS) $? -o $@

obj:
	mkdir $(OBJ)

#%: %.o $(OBJS) langlex.o
#	$(CC) $(COPTS) $(OBJS) langlex.o $? -o $@

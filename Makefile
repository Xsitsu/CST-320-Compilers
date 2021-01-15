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

PROGS = lang
TESTPROGS = test_scanner

all: $(PROGS)

test: buildt runt

buildt: $(TESTPROGS)

runt:
	xtest/test

clean:
	rm -f $(OBJ)/*.o
	rmdir $(OBJ)
	rm -f $(PROGS)
	rm -f $(TESTPROGS)
	rm -f langlex.c
	rm -f langlex.o
	rm -f out.xml
	rm -f out2.xml

$(PROGS): $(OBJS) $(OBJ)/$(PROGS).o
	$(CC) $(OBJS) $(OBJ)/$(PROGS).o langlex.o -o $@

$(OBJ)/$(PROGS).o: $(PROGS).cpp langlex.o
	$(CC) $(COPTS) $(PROGS).cpp -o $(OBJ)/$(PROGS).o

$(TESTPROGS): $(OBJS) $(OBJ)/$(TESTPROGS).o
	$(CC) $(OBJS) $(OBJ)/$(TESTPROGS).o langlex.o -o $@

$(OBJ)/$(TESTPROGS).o: $(TESTPROGS).cpp langlex.o
	$(CC) $(COPTS) $(TESTPROGS).cpp -o $(OBJ)/$(TESTPROGS).o

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

$(OBJ)/%.o: $(SRC)/%.cpp obj
	$(CC) $(COPTS) $? -o $@

obj:
	mkdir $(OBJ)

# Makefile for common dir in Sudoku

PROG = commontest

OBJS = sudokustruct.o
LIB = common.a

UNITTEST=-DGAUNTLET
CREATETEST=-DTESTCREATE

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS)
CC = gcc
MAKE = make

$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)

sudokustruct.o: sudokustruct.h

$(PROG): sudokustruct.c
	$(CC) $(CFLAGS) $(CREATETEST) $^ -o $@

.PHONY: test clean

test: $(PROG)
	./$(PROG)

clean:
	rm -f common.a
	rm -f core
	rm -f *~ *.o
	rm -f $(PROG)
	rm -f $(WORD)
	rm -f $(INDEX)

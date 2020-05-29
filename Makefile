# Makefile for Sudoku Puzzle

PROG = sudoku

C = common

CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$C 
CC = gcc

MAKE = make

LLIBS = $C/common.a 

.PHONY: all clean

all:
	$(MAKE) -C common

$(PROG): $(PROG).o $(LLIBS) 
	$(CC) $(CFLAGS) $^ -o $@
	
test: all $(PROG)
	./$(PROG)

clean:
	rm -f core
	rm -f sudoku
	rm -f *~ *.o
	rm -rf *.dSYM
	rm -f TAGS
	$(MAKE) -C common clean
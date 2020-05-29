# Makefile for Sudoku Puzzle

MAKE = make
.PHONY: all valgrind clean

all:
	$(MAKE) -C common

clean:
	rm -f *~
	rm -f TAGS
	$(MAKE) -C common clean
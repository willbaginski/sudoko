# Makefile for Sudoku Puzzle

C = common

CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$C 
CC = gcc

MAKE = make

LLIBS = $C/common.a 

all: common fuzztesting sudoku

sudoku: sudoku.o $(LLIBS) 
	$(CC) $(CFLAGS) $^ -o $@

common:
	$(MAKE) -C common

fuzztesting: fuzztesting.o $(LLIBS)
	$(CC) -Wall -pedantic -std=gnu -ggdb $(FLAGS) -I$L -I$C $^ -o fuzztesting

fuzztesting.o: fuzztesting.c

.PHONY: all clean
	
# test: all $(PROG)
# 	./$(PROG)
test: all $(PROG)
	bash -v ./testing.sh

valgrind:
	#valgrind --leak-check=full --show-leak-kinds=all ./sudoku create easy
	valgrind --leak-check=full --show-leak-kinds=all ./sudoku solve < ./common/test1.txt

clean:
	rm -f core
	rm -f sudoku
	rm -f *~ *.o
	rm -rf *.dSYM
	rm -f TAGS
	$(MAKE) -C common clean
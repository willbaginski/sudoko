# Makefile for Sudoku Puzzle

PROG = sudoku

C = common

CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$C 
CC = gcc

MAKE = make

LLIBS = $C/common.a 

$(PROG): $(PROG).o $(LLIBS) 
	$(CC) $(CFLAGS) $^ -o $@

fuzztesting: fuzztesting.o $(LLIBS)
	$(CC) -Wall -pedantic -std=gnu -ggdb $(FLAGS) -I$L -I$C $^ -o fuzztesting

fuzztesting.o: fuzztesting.c

.PHONY: all clean

all: fuzztesting
	$(MAKE) -C common

	
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
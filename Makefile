# Makefile for Sudoku Puzzle

# object files, and the target library
OBJS = sudoku.o
PROG = sudoku
LLIBS = $C/common.a 

C = common

CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$C 
CC = gcc

MAKE = make

LLIBS = $C/common.a 

$(PROG): $(OBJS) $(LLIBS) 
	$(CC) $(CFLAGS) $^ -o $@

$(LLIBS):
	$(MAKE) -C common

fuzztesting: fuzztesting.o $(LLIBS)
	$(CC) -Wall -pedantic -std=gnu -ggdb $(FLAGS) $^ -o fuzztesting

fuzztesting.o: fuzztesting.c

all: $(LLIBS) fuzztesting $(PROG) 

.PHONY: all clean
	
test: all $(PROG)
	bash -v ./testing.sh

valgrind:
	#valgrind --leak-check=full --show-leak-kinds=all ./sudoku create easy
	valgrind --leak-check=full --show-leak-kinds=all ./sudoku solve < ./common/test1.txt

fuzz:
	./fuzztesting 1

clean:
	rm -f core
	rm -f sudoku
	rm -f fuzztesting
	rm -f *~ *.o
	rm -rf *.dSYM
	rm -f TAGS
	$(MAKE) -C common clean
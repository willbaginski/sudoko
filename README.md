# CS50 Final Project Sudoku
## Antony 1, CS50, May 2020

### sudoku

The `sudoku` is a standalone program that has two modes: *create* and *solve*. 
In the *create* mode, the program takes in a second parameter: 'easy', 'medium', or 'hard', and produces a puzzle through stdout with the appropriate difficulty.
In *solve* mode, the program reads and loads and puzzle then solves using backtracing.

This is our graphical interpretation of sudoko [website] (http://home.cs.dartmouth.edu/~olee/) and this is the [repo] (https://github.com/oleedart/sudoku-web). 
### Usage

To use the sudoku, execute from a command line with usage syntax:
`./sudoku gameOption [difficulty]`

### Implementation

The specific implementation and pseudocode is described in IMPLEMENTATION.md.

`indexer` parses parameters, creates data struct, calls index_build and index_save

`indextest` parses parameters, creates data struct, calls index_load and index_save

The following helper methods are used from common.a:

*sudoku_load*, which converts stdin to a sudoku data structures

*sudoku_build*, which creates a sudoku data structure of the specified dificulty

*sudoku_solve*, which solves the puzzle forwards and backwards using the backtracing algorithm and returns an int of how many unique solutions the puzzle has

*sudoku_print*, which takes a sudoku data structures and prints it to stdout following the specified format

*sudoku_validate*, which take a sudoku data structure, row, and column and returns a boolean i the number placed in that location is valid

*sudoku_delete*, which frees the memory allocated for the sudoku data structure


### Assumptions

No assumptions beyond those that are clear from the spec. The solver will even work with invalid sudoku puzzles and produce a 'no solutions' message.

`sudoku.c` only allows the user to choose a preset difficulty options where easy, medium, and hard correspond to 45, 40, and 35 clues.
The code used to build puzzles, however, supports the creation of sudokus with as few as 26 clues without error (or extremely rare error).

25 clues is generally supported as well, but the creation process occasioanlly (estimated ~15% of the time) fails.
It is believed that such failures are caused by stack overflows.

24 clue puzzles are possible to generate but not consistently.

Limited testing was performed on puzzles with fewer than 24 clues, but valid solutions at that level are rare.
It is unlikely that such puzzles can be consistenly generated


### Compilation

To compile, simply `make`.

To compile common archive as well, simply `make all`.

To test, simply `make test`.
See [TESTING](TESTING.md) for details of testing and an example test run.

To test memory leaks, simply `make valgrind`.




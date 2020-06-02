# CS50 Final Project Sudoku
## Antony 1, CS50, May 2020

### sudoku

The `sudoku` is a standalone program that has two modes: *create* and *solve*. 
In the *create* mode, the program takes in a second parameter: 'easy', 'medium', or 'hard', and produces a puzzle through stdout with the appropriate difficulty.
In *solve* mode, 

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


### Compilation

To compile, simply `make`.

To compile common archive as well, simply `make all`.

To test, simply `make test`.
See [TESTING](TESTING.md) for details of testing and an example test run.

To test memory leaks, simply `make valgrind`.




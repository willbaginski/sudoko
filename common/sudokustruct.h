/**
 * Sudoku.h
 * Contains the functions for Sudoku generation, loading, and solving
 * Authors: Antony 1, Spring 2020
 * 
*/

#include <stdbool.h>

typedef struct sudoku sudoku_t;

/* allocates memory for the 9x9 int array sudoku */
sudoku_t *new_sudoku();

/* Fills a sudoku data struct from data from stdin
* Reads in the digits of a sudoku board from sdtin, validates that the number is correct
* and places them in the appropriate location in the 9x9 integer array */
bool sudoku_load(sudoku_t *sudoku);

/* builds a sudoku puzzle with spaces removed
 * takes a sudoku struct with an empty puzzle and fills it entirely so that it resembles a solved puzzle
 * then removes spaces while making sure that the partially-empty puzzle only have one solution (and is a valid sudoku)
 * from a total of 81 spaces, leaves *clues* spaces filled and 81 - *clues* spaces empty */
bool sudoku_build(sudoku_t *sudoku, int clues);

/* solves a the inputed sudoku data struct
* Uses the backtracing method to place numbers in the empty spaces. Then continues until it cannot place a number
* then the algorithm will return false and trigger backtracing. 
* This solution has been optimized to not loop through every solution and only loop through numbers that are possible solutions.
* Additionally, this function solves both forwards and backwards in order to check unqiue solutions. 
* The function also takes a boolean to tell it whether or not to print out the solved puzzle.
* The function returns 0 for no solution, 1 for one solutions, and 2 for two or more solutions. */
int sudoku_solve(sudoku_t *sudoku, bool print);

/* takes a given sudoku struct and prints each row, print each value in each column for row */
bool sudoku_print(sudoku_t *sudoku);

/* takes a sudoku structure and frees the space allocated for that structure */
bool sudoku_delete(sudoku_t *sudoku);

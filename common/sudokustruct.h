/**
 * Sudoku.h
 * Contains the functions for Sudoku generation, loading, and solving
 * Authors: Antony 1, Spring 2020
 * 
*/

#include <stdbool.h>

typedef struct sudoku sudoku_t;

sudoku_t *new_sudoku();

bool sudoku_load(sudoku_t *sudoku);

/* builds a sudoku puzzle with spaces removed
 * takes a sudoku struct with an empty puzzle and fills it entirely so that it resembles a solved puzzle
 * then removes spaces while making sure that the partially-empty puzzle only have one solution (and is a valid sudoku)
 * from a total of 81 spaces, leaves *clues* spaces filled and 81 - *clues* spaces empty */
bool sudoku_build(sudoku_t *sudoku, int clues);

int sudoku_solve(sudoku_t *sudoku, bool print);

bool sudoku_print(sudoku_t *sudoku);

bool sudoku_validate(sudoku_t *sudoku, int row, int column);

bool sudoku_delete(sudoku_t *sudoku);

/**
 * Sudoku.h
 * Contains the functions for Sudoku generation, loading, and solving
 * Authors: Antony 1, Spring 2020
 * 
*/

#include <stdbool.h>

typedef struct sudoku sudoku_t;

bool sudoku_load(sudoku_t *sudoku);

bool sudoku_build(sudoku_t *sudoku);

bool sudoku_solve(sudoku_t *sudoku);

bool sudoku_print(sudoku_t *sudoku);

bool sudoku_delete(sudoku_t *sudoku);


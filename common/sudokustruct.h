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

bool sudoku_build(sudoku_t *sudoku, int clues);

int sudoku_solve(sudoku_t *sudoku);

bool sudoku_print(sudoku_t *sudoku);

bool sudoku_validate(sudoku_t *sudoku, int row, int column);

bool sudoku_delete(sudoku_t *sudoku);

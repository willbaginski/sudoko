/**
 * code for sudoku functionality
 * Authors: Antony 1, Spring 5/27/2020
 * 
*/

typedef struct sudoku {
    int puzzle[9][9];
    counters_t* num_count;
} sudoku_t;
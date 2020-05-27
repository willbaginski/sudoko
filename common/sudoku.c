/**
 * code for sudoku functionality
 * Authors: Antony 1, Spring 5/27/2020
 * 
*/

#include "sudoku.h"

typedef struct sudoku {
    int puzzle[9][9];
} sudoku_t;

bool sudoku_load(sudoku_t *sudoku) {

}

bool sudoku_build(sudoku_t *sudoku) {

}

bool sudoku_solve(sudoku_t *sudoku) {

}

bool sudoku_print(sudoku_t *sudoku) {

    if(sudoku == NULL) {
        return false;
	}

    // Print the the puzzle
	for (int r = 0; r < 9; r++) {
		for (int c = 0; c < 9; c++) {
			fprintf(stdout, "%d "sudoku->puzzle[r][c]);
		}
		fprintf(stdout, "\n");
	}
}

bool sudoku_delete(sudoku_t *sudoku) {
	if(sudoku != NULL) {
		free(sudoku);
	}
}

// Testing code. Run it through the mega gauntlet
#ifdef GAUNTLET



#endif

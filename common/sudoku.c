/**
 * code for sudoku functionality
 * Authors: Antony 1, Spring 5/27/2020
 * 
*/

#include <stdbool.h>
#include <string.h>

#include "sudoku.h"


typedef struct sudoku {
    int puzzle[9][9];
} sudoku_t;

/* Takes in from stdin, loads into the suduko data structure */
bool sudoku_load(sudoku_t *sudoku) {
	int n1,n2,n3,n4,n5,n6,n7,n8,n9;
	char[] line;
	int row = 0;
	while((fscanf(stdin, "%d %d %d %d %d %d %d %d %d ", &n1, &n2, &n3, &n4, &n5, &n6, &n7, &n8, &, &n9)) == 9){
		for(int col = 0; col < 9; col ++){
			//create variable name
			char name[2];
			strcpy(name, "n");
			char num;
			sprintf(num, "%d", col+1); 
			strcat(name, num);

			printf("the number is %d\n", name);

			//confirm validity
			if(name < 0 || name > 9){
				fprintf(stderr, "Error: invalid sudoko entry.\n")
				return false;
			}
			//add to data structure
			sudoku->puzzle[row][col] = name;
		}
	}
	if(row == 8){
		return true;
	}
	fprintf(stderr, "Error: invalid sudoko grid.\n")
	return false;
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

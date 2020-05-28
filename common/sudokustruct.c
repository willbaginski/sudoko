/**
 * code for sudoku functionality
 * Authors: Antony 1, Spring 5/27/2020
 * 
*/

#include <stdbool.h>
#include <string.h>

#include "sudoku.h"

/* sudoku data structure */
typedef struct sudoku {
    int puzzle[9][9];
} sudoku_t;

/* sudoku_validate helper functions */
bool check_row(sudoku_t *sudoku, int row);
bool check_col(sudoku_t *sudoku, int col);
bool check_square(sudoku_t *sudoku, int row, int col);

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
    for(int row = 0; row < 9; row++){
        for(int col = 0; col < 9; col++){
			//check if sudoko space is empty
			if(suduko->puzzle[row][col] == 0){
				//find value not in row, col or square
				//place val
				//check full
			}
		}
	}
}

/* helper for sudoko_solve */
bool check_full(suduko_t *suduko){
    for(int row = 0; row < 9; row++){
        for(int col = 0; col < 9; col++){
            if(sudoko->puzzle[row][col] == 0){
                return false;
            }
        }
    }
    return true;
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

/*	sudoku_validate method	*/
// checks that there are no collisions for the row, column, and square around the current point
bool sudoku_validate(sudoku_t *sudoku, int row, int column){

	// check sudoku exists
	if (sudoku == NULL){

		// throw error and return false
		fprintf(stderr, "error: must pass valid sudoku board\n");
		return false;
	}

	// call check_row, col, and square
	if (!check_row(sudoku, row) || !check_col(sudoko, col) || !check_square(sudoku, row, col)){
		
		// return false if any of them failed
		return false;
	}

	// return true
	return true;
}

/*	check_row helper method	*/
bool check_row(sudoko_t *sudoko, int row){
	
	// create array for checking row
	int rowcount[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

	// loop through the row and check that each integer only occurs once (except for 0)
	for (int colnum = 0; colnum < 9; colnum++){

		// get the int at this spot
		int num = sudoku->puzzle[row][colnum];

		// don't check if the num is 0
		if (num != 0){

			// check the count in the rowcount array
			if (rowcount[num - 1] != 0){

				// return false if we've already seen this num
				return false;
			}
			
			// otherwise, increment the count
			rowcount[num - 1] += 1;
		}
	}

	// return true if no errors occured
	return true;
}

/*	check_col helper method	*/
bool check_col(sudoko_t *sudoko, int col){
	
	// create array for checking col
	int colcount[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

	// loop through the row and check that each integer only occurs once (except for 0)
	for (int rownum = 0; rownum < 9; rownum++){

		// get the int at this spot
		int num = sudoku->puzzle[rownum][col];

		// don't check if the num is 0
		if (num != 0){

			// check the count in the colcount array
			if (colcount[num - 1] != 0){

				// return false if we've seen this num
				return false;
			}
			
			// otherwise, increment the count
			colcount[num - 1] += 1;
		}
	}

	// return true if no errors occured
	return true;
}

/*	check_square helper method	*/
bool check_square(sudoku_t *sudoku, int row, int col){

	// variables for the row and column bottom left corner
	int rowcorner;
	int colcorner;

	// array for checking ints in the square
	int sqarecount[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

	// get the row number for the bottom left corner of the square
	if (row < 3){
		rowcorner = 0;
	}
	else if (row < 6){
		rowcorner = 3;
	}
	else{
		rowcorner = 6;
	}

	// get the column number for the square's bottom left corner
	if (col < 3){
		colcorner = 0;
	}
	else if (col < 6){
		colcorner = 3;
	}
	else{
		colcorner = 6;
	}

	// loop through the square
	for (int x = rowcorner; x < rowcorner + 3; x++){
		for (int y = colcorner; y < colcorner + 3; y++){

			// get the number at the current slot
			int num = sudoku->puzzle[x][y];

			// don't check if the num is 0
			if (num != 0){

				// check the count in the colcount array
				if (squarecount[num - 1] != 0){

					// return false
					return false;
				}
			
				// otherwise, increment the count
				squarecount[num - 1] += 1;
			}
		}

		// return true if no collisions found
		return true;
	}
}

// Testing code. Run it through the mega gauntlet
#ifdef GAUNTLET



#endif

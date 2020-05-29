/**
 * code for sudoku functionality
 * Authors: Antony 1, Spring 5/27/2020
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "sudokustruct.h"

/* sudoku data structure */
typedef struct sudoku {
    int puzzle[9][9];
} sudoku_t;

sudoku_t* new_sudoku(){
	int grid[9][9]; 
	sudoku_t *game = calloc(1, sizeof(grid));
	if(game == NULL){
		fprintf(stderr, "Error: cannot allocate space for sudoku. \n");
		return NULL;
	}
	return game;
}


/* sudoku_validate helper functions */
int *check_row(sudoku_t *sudoku, int row);
int *check_col(sudoku_t *sudoku, int col);
int *check_square(sudoku_t *sudoku, int row, int col);
int *find_options(int array[]);

/* other helper functions */
bool check_full(sudoku_t *sudoku);
bool check_empty(sudoku_t *sudoku);
int *get_options(sudoku_t *sudoku, int row, int col);

/* Takes in from stdin, loads into the suduko data structure */
bool sudoku_load(sudoku_t *sudoku) {

	for(int row = 0; row < 9; row++){
        for(int col = 0; col < 9; col++){
			int num;
			fscanf(stdin, " %d", &num);
			//check validity
			if(num < 0 || num > 9){
				fprintf(stderr, "Error: invalid sudoko entry.\n");
				return false;
			}
			//add to data structure
			sudoku->puzzle[row][col] = num;
		}
	}
	return true;
}

/* takes an empty sudoku and populates it randomly
 * will eventually be valid and support square removal
 * but for now will randomly populate a grid */
bool sudoku_build(sudoku_t *sudoku) {
	// make sure sudoku is empty
	if (! check_empty(sudoku)) {
		return false;
	}
	// now that we know it is empty, populate the grid
	// use the time as a seed for random number generation
	srand(time(NULL));
	
	// num will be the number, 1-9, which is currently being inserted into the puzzle
	for (int num = 1; num < 10; num++) {
		// go through columns, randomly selecting a row num 0-8 to place num into
		for (int col = 0; col < 8; col ++) {
			int row = rand() % 9 + 1;
			// "reroll" row index until the entry isn't conflicting
			// this isn't very effecient -- instead we should keep track of collisions ... update later
			while (! sudoku_validate(sudoku, row, col)) {
				row = rand() % 9 + 1;
			}
			
		}
	}
	// now that we have a full, valid grid, we can selectively remove from it
	// for now, randomly remove a random number of squares in the range [25, 40]
	for (int empty = rand() % 16 + 25; empty > 0; empty--) {
		// choose a random filled position
		int row = rand() % 9;
		int col = rand() % 9;
		while (sudoku->puzzle[row][col] == 0) {
			row = rand() % 9;
			col = rand() % 9;
		}
		// replace its value with 0
		sudoku->puzzle[row][col] = 0;
	}
}

int sudoku_solve(sudoku_t *sudoku) {
	//check to see if the grid needs solving
	if(check_full(sudoku)){
		return 1; 
	}

    for(int row = 0; row < 9; row++){
        for(int col = 0; col < 9; col++){
			//check if sudoko space is empty
			if(sudoku->puzzle[row][col] == 0){
				//find value not in row, col or square
				for(int val = 0; val < 9; val++){
					//try placing a value
					sudoku->puzzle[row][col] = val+1;
					if(sudoku_validate(sudoku, row, col) == true){	//valid place
						//recursive call
						if(sudoku_solve(sudoku)){
							//you have foud oe solution, try to go back and find more
						}
					}
					sudoku_print(sudoku);
					printf("--------\n");
				}
				sudoku->puzzle[row][col] = 0; //means couldn't find a number to place

				//copy board here to check for unique solutions
	
			}
		}
	}
	return 0;	//default false, breakout if true
}

/* helper for sudoko_solve */
bool check_full(sudoku_t *sudoku){
    for(int row = 0; row < 9; row++){
        for(int col = 0; col < 9; col++){
            if(sudoku->puzzle[row][col] == 0){
                return false;
            }
        }
    }
    return true;
}

/* helper for sudoku_load */
bool check_empty(sudoku_t *sudoku) {
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			if (sudoku->puzzle[row][col] != 0) {
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
			fprintf(stdout, "%d ", sudoku->puzzle[r][c]);
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
	if (check_row(sudoku, row) == NULL || check_col(sudoku, column) == NULL || check_square(sudoku, row, column) == NULL){
		
		// return false if any of them failed
		return false;
	}

	// return true
	return true;
}

/* get_options method */
// returns which ints (if any) can go into a given spot
int *get_options(sudoku_t *sudoku, int row, int col){

	// check that the board is not null
	if (sudoku == NULL){

		// throw an error and return NULL
		fprintf(stderr, "error: must pass valid sudoku board\n");
		return NULL;
	}

	// call check row, col, and square
	int rowoptions[] = check_row(sudoku, row);
	int coloptions[] = check_col(sudoku, col);
	int squareoptions[] = check_square(sudoku, row, col);

	// initialize an array for options
	int options[9] = { 0 };

	// loop through indices, check if each element is found in all options arrays
	for (int i = 0; i < 10; i++){

		if (rowoptions[i] == 1 && coloptions[i] == 1 && squareoptions[i] == 1){

			// add this element to the overarching options array
			options[i] = 1;
		}
	}

	// NOTE: THE INDICES IN THE OPTIONS ARRAY CORRESPOND TO AVAILABLE NUMBERS
	// BUT ARE OFFSET BY 1 (SO INDEX 0 CORRESPONDS TO 1, ETC)
	return options;
}

/*	check_row helper method	*/
int *check_row(sudoku_t *sudoko, int row){
	
	// create array for checking row
	int rowcount[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

	// loop through the row and check that each integer only occurs once (except for 0)
	for (int colnum = 0; colnum < 9; colnum++){

		// get the int at this spot
		int num = sudoko->puzzle[row][colnum];

		// don't check if the num is 0
		if (num != 0){

			// check the count in the rowcount array
			if (rowcount[num - 1] != 0){

				// return NULL if we've already seen this num
				return NULL;
			}
			
			// otherwise, increment the count
			rowcount[num - 1] += 1;
		}
	}

	// get the options for what int can go in this slot
	int options[] = find_options(rowcount);

	// return the options array if no collisions found
	return options;
}

/*	check_col helper method	*/
int *check_col(sudoku_t *sudoko, int col){
	
	// create array for checking col
	int colcount[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

	// loop through the row and check that each integer only occurs once (except for 0)
	for (int rownum = 0; rownum < 9; rownum++){

		// get the int at this spot
		int num = sudoko->puzzle[rownum][col];

		// don't check if the num is 0
		if (num != 0){

			// check the count in the colcount array
			if (colcount[num - 1] != 0){

				// return NULL if we've seen this num
				return NULL;
			}
			
			// otherwise, increment the count
			colcount[num - 1] += 1;
		}
	}
	
	// get the options for what int can go in this slot
	int options[] = find_options(colcount);

	// return the options array if no collisions found
	return options;
}

/*	check_square helper method	*/
int *check_square(sudoku_t *sudoku, int row, int col){

	// variables for the row and column bottom left corner
	int rowcorner;
	int colcorner;

	// array for checking ints in the square
	int squarecount[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

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

					// return NULL
					return NULL;
				}
			
				// otherwise, increment the count
				squarecount[num - 1] += 1;
			}
		}
	}

	// get the options for what int can go in this slot
	int options[] = find_options(squarecount);

	// return the options array if no collisions found
	return options;
}

/*	find_options helper method */
// find the numbers that can go in a particular spot, given the count array
int *find_options(int array[]){

	// initialize an array with all zeros
	int options[9] = { 0 };

	// loop through the passed array (skip over index 0)
	for (int i = 1; i < 10; i++){

		// if any of the indices store 0, add this index to the options array
		if (array[i] == 0){

			options[i - 1] = 1;
		}
	}

	return options;
}

// Testing code. Run it through the mega gauntlet
#ifdef GAUNTLET

int main() {

	//future test code here

	printf("Test\n");
	sudoku_t* puzzle = new_sudoku();
	sudoku_load(puzzle);
	sudoku_print(puzzle);

	sudoku_solve(puzzle);
	sudoku_print(puzzle);

	return 0;
}

#endif
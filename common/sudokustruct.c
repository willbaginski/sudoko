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
#include "intpair.h"

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
	#ifdef GAUNTLET
		printf("Created new 9x9 sudoku\n");
	#endif
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
void copy_puzzle(sudoku_t *dest, sudoku_t *source);
bool fill_puzzle(sudoku_t *sudoku, int row, int col);
bool remove_squares(sudoku_t *sudoku, int remove);

/* Takes in from stdin, loads into the suduko data structure */
bool sudoku_load(sudoku_t *sudoku) {
	// loop through all the numbers in the board
	for(int row = 0; row < 9; row++){
        for(int col = 0; col < 9; col++){
			int num;
			if(fscanf(stdin, " %d", &num) != 1){	//checks stdin has 81 numbers
				fprintf(stderr, "Error: invalid sudoko board.\n");
				return false;
			}	
			//check validity
			if(num < 0 || num > 9){
				fprintf(stderr, "Error: invalid sudoko entry.\n");
				return false;
			}
			//add to data structure
			sudoku->puzzle[row][col] = num;
		}
	}
	#ifdef GAUNTLET
		printf("Successfully loaded sudoku\n");
	#endif
	return true;
}

/* takes an empty sudoku and populates it randomly
 * clues is the number of filled squares at the end */
bool sudoku_build(sudoku_t *sudoku, int clues) {
	// make sure sudoku is empty
	if (! check_empty(sudoku)) {
		return false;
	}

	// seed the random number generator
	srand(time(NULL));

	// construct a solved/full grid
	fill_puzzle(sudoku, 0, 0);
	
	//printf("\nSudoku with %d filled-in slots and %d empty slots:\n", clues, 81-clues);
	// remove spaces
	remove_squares(sudoku, 81 - clues);

	
  #ifdef GAUNTLET
		printf("Successfully built sudoku\n");
	#endif
	return true;
}

/* fills an empty sudoku puzzle randomly with a valid full grid
 * helper for sudoku_build */
bool fill_puzzle(sudoku_t *sudoku, int row, int col) {
	// if puzzle is full, return true (base case)
	if (check_full(sudoku)) {
		return true;
	}
	
	// find valid entries for the spot [row][col]
	int *options = get_options(sudoku, row, col);
	// determine the number of valid options
	int valid = 0;
	for (int i = 0; i < 9; i++) {
		if (options[i] == 1) {
			valid++;
		}
	}
	// if valid is 0, there are no valid options for this slot and we need to backtrack!
	if (valid == 0) {
		free(options);
		return false;
	}

	/* turn the array from get_options into a form which can be randomly iterated over more easily
	 * allocate an int array that can hold one entry per valid option for the spot */
	int *formatted_options = calloc(valid, sizeof(valid));
	/* add each valid number into the array
	 * ex: if 2, 4, 7 were valid, resultant array is: { 2, 4, 7 }
	 * j will end up equaling the last valid index into the array */
	int j = 0;
	for (int i = 0; i < 9; i++) {
		if (options[i] == 1) {
			formatted_options[j] = i + 1;
			j++;
		}
	}
	free(options);

	// randomly select an int from formatted_options and insert it into the slot
	int original_num = rand() % j;
	int num = original_num;
	sudoku->puzzle[row][col] = formatted_options[num];
	
	/* grab the row and col to move to the next spot (moving left to right, then top to bottom)
	 * (save them as new values instead of incrementing the current ones because the old values are
	 * still needed in order to retry fill_puzzle with a different value in the current slot) */
	int next_row, next_col;
	if (col == 8) {
		next_col = 0;
		next_row = row + 1;
	} else {
		next_col = col + 1;
		next_row = row;
	}

	while (! fill_puzzle(sudoku, next_row, next_col)) {
		// move on to the next index in formatted_options (if we get to the end (j - 1), go back to the start)
		if (num == j - 1) {
			num = 0;
		} else {
			num++;
		}
		// replace the current value in the puzzle with the next one
		sudoku->puzzle[row][col] = formatted_options[num];
		// if num gets back to original_num, we've tried every option and none of them worked ... return false
		if (num == original_num) {
			// clean up
			sudoku->puzzle[row][col] = 0;
			free(formatted_options);
			return false;
		}
	}

	// clean up
	free(formatted_options);
	return true;
}

/* removes slots in the puzzle */
bool remove_squares(sudoku_t *sudoku, int remove) {
	// determine the number of slots left to empty
	int removed = 0;
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			if (sudoku->puzzle[row][col] == 0) {
				removed++;
			}
		}
	}
	
	// base cases
	if (sudoku_solve(sudoku, false) != 1) {  // backtrack if sudoku doesn't have a unique solution
		return false;
	} else if (removed == remove) {  // if we get here, we're finished
		return true;
	}

	// allocate an array with an entry for every filled square
	intpair_t **options = calloc(81 - removed, sizeof(intpair_t *));
	// fill the array with an intpair containing the position of every nonzero/filled spot
	int filled = 0;
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			if (sudoku->puzzle[row][col] != 0) {
				options[filled] = new_intpair(row, col);
				filled++;
			}
		}
	}

	// take a random spot from options, save its value, and remove it
	int original_index = rand() % filled;
	int index = original_index;
	int row = intpair_getRow(options[index]);
	int col = intpair_getCol(options[index]);
	int value = sudoku->puzzle[row][col];
	sudoku->puzzle[row][col] = 0;

	// recursive case ... if what we inserted invalidates the puzzle, try different options until we have a unique solution again
	while (sudoku_solve(sudoku, false) != 1 || ! remove_squares(sudoku, remove)) {
		// restore the old value (removing it caused an issue!)
		sudoku->puzzle[row][col] = value;

		// grab the next nonzero square from options
		if (index == filled - 1) {  // wrap back to the start of the array
			index = 0;
		} else {
			index++;
		}
		
		// check if we have already tried and failed to find a unique solution for every spot (backtrack if we have)
		if (index == original_index) {
			for (int i = 0; i < filled; i++) {
				intpair_delete(options[i]);
			}
			free(options);
			return false;
		}

		// if we still have spots to try, take the next row and col from options and try that spot
		row = intpair_getRow(options[index]);
		col = intpair_getCol(options[index]);
		// save the value there
		value = sudoku->puzzle[row][col];
		// empty the square/set the position to zero
		sudoku->puzzle[row][col] = 0;
	}

	// clean up and return true
	for (int i = 0; i < filled; i++) {
				intpair_delete(options[i]);
			}
			free(options);
	return true;
}

bool sudoku_solve_forwards(sudoku_t *sudoku) {
	//check to see if the grid needs solving
	if(check_full(sudoku)){
		return true;	
	}

	//go through the entire board
    for(int row = 0; row < 9; row++){
        for(int col = 0; col < 9; col++){
			//check if sudoko space is empty
			if(sudoku->puzzle[row][col] == 0){
				//loop through all possible values
				// find valid entries for the spot [row][col]
				int *options = get_options(sudoku, row, col);
				// determine the number of valid options
				int valid = 0;
				for (int i = 0; i < 9; i++) {
					if (options[i] == 1) {
						valid++;
					}
				}
				// if valid is 0, there are no valid options for this slot and we need to backtrack!
				if (valid == 0) {
					free(options);
					return false;
				}

				int *formatted_options = calloc(valid, sizeof(int));
				// add each valid number into the array
				int j = 0;
				for (int i = 0; i < 9; i++) {
					if (options[i] == 1) {
						formatted_options[j] = i + 1;
						j++;
					}
				}

				free(options);

				//now try to solve sudoku
				for(int val = 0; val < valid; val++){
					//try placing a value
					sudoku->puzzle[row][col] = formatted_options[val];
					//clean up arrays
					if(sudoku_validate(sudoku, row, col)){	//valid place
						//recursive call
						if(sudoku_solve_forwards(sudoku)){
							free(formatted_options);
							return true;
						}
					}
				}
				if(formatted_options != NULL){
					free(formatted_options);
				}
				sudoku->puzzle[row][col] = 0; //means couldn't find a number to place
				return false;
			}
		}
	}
	return false;
}

bool sudoku_solve_backwards(sudoku_t *sudoku) {
	//check to see if the grid needs solving
	if(check_full(sudoku)){
		return true;	
	}

	//go through the entire board
    for(int row = 0; row < 9; row++){
        for(int col = 0; col < 9; col++){
			//check if sudoko space is empty
			if(sudoku->puzzle[row][col] == 0){
				// find valid entries for the spot [row][col]
				int *options = get_options(sudoku, row, col);
				// determine the number of valid options
				int valid = 0;
				for (int i = 0; i < 9; i++) {
					if (options[i] == 1) {
						valid++;
					}
				}
				// if valid is 0, there are no valid options for this slot and we need to backtrack!
				if (valid == 0) {
					free(options);
					return false;
				}

				int *formatted_options = calloc(valid, sizeof(int));
				// add each valid number into the array
				int j = 0;
				for (int i = 0; i < 9; i++) {
					if (options[i] == 1) {
						formatted_options[j] = i + 1;
						j++;
					}
				}
				free(options);

				//now try to solve sudoku
				for(int val = valid-1; val >= 0; val--){
					//try placing a values
					sudoku->puzzle[row][col] = formatted_options[val];
					

					if(sudoku_validate(sudoku, row, col)){	//valid place
						//recursive call
						if(sudoku_solve_backwards(sudoku)){
							free(formatted_options);
							return true;
						}
					}
					
				}
				if(formatted_options != NULL){
					free(formatted_options);
				}
				sudoku->puzzle[row][col] = 0; //means couldn't find a number to place
				return false;
			}
		}
	}
	return false;
}

/* solve overall */
int sudoku_solve(sudoku_t* sudoku, bool print){
	sudoku_t* one = new_sudoku();
	sudoku_t* two = new_sudoku();

	copy_puzzle(one, sudoku);	
	copy_puzzle(two, sudoku);

	//solve both puzzle copies forward and backwards
	if(!sudoku_solve_forwards(one) || !sudoku_solve_backwards(two)){	//unable to solve board
		sudoku_delete(one);
		sudoku_delete(two);
		return 0;
	}

	//print the answer
	if(print){
		sudoku_print(two);
	}
	
	#ifdef GAUNTLET
	sudoku_print(one);
	printf("-----\n");
	sudoku_print(two);
	#endif

	//go through the entire board to compare outputs
    for(int row = 0; row < 9; row++){
        for(int col = 0; col < 9; col++){
			if(one->puzzle[row][col] != two->puzzle[row][col]){	//means more than one board solution
				sudoku_delete(one);
				sudoku_delete(two);
				return 2;
			}
		}
	}
	sudoku_delete(one);
	sudoku_delete(two);
	return 1;	//default one board solution
	
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
	return true;
}

bool sudoku_delete(sudoku_t *sudoku) {
	if(sudoku != NULL) {
		free(sudoku);
		return true;
	}
	return false;
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
	int *rowoptions = check_row(sudoku, row);
	int *coloptions = check_col(sudoku, column);
	int *squareoptions = check_square(sudoku, row, column);
	if (rowoptions == NULL || coloptions == NULL || squareoptions == NULL){
		// clean up
		if (rowoptions != NULL) {
			free(rowoptions);
		}
		if (coloptions != NULL) {
			free(coloptions);
		}
		if (squareoptions != NULL) {
			free(squareoptions);
		}

		// return false if any of them failed
		return false;
	}
	// clean up
	free(rowoptions);
	free(coloptions);
	free(squareoptions);
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
	int *rowoptions = check_row(sudoku, row);
	int *coloptions = check_col(sudoku, col);
	int *squareoptions = check_square(sudoku, row, col);
	
	// initialize an array for options
	int *options = malloc(sizeof(int) * 9);

	// loop through indices, check if each element is found in all options arrays
	for (int i = 0; i < 9; i++){
		if (rowoptions[i] == 1 && coloptions[i] == 1 && squareoptions[i] == 1){
			
			// add this element to the overarching options array
			options[i] = 1;
		} else {
			options[i] = 0;
		}
	}

	// NOTE: THE INDICES IN THE OPTIONS ARRAY CORRESPOND TO AVAILABLE NUMBERS
	// BUT ARE OFFSET BY 1 (SO INDEX 0 CORRESPONDS TO 1, ETC)
	free(rowoptions);
	free(coloptions);
	free(squareoptions);
	return options;
}

/*	check_row helper method	*/
int *check_row(sudoku_t *sudoko, int row){
	// create array for checking row
	int rowcount[9] = { 0 };
	// loop through the row and check that each integer only occurs once (except for 0)
	for (int colnum = 0; colnum < 9; colnum++){
	
		// get the int at this spot
		int num = sudoko->puzzle[row][colnum];
		
		//printf("checking row: %d col: %d, num is %d\n", row, colnum, num);

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
	int *options = find_options(rowcount);

	// return the options array if no collisions found
	return options;
}

/*	check_col helper method	*/
int *check_col(sudoku_t *sudoko, int col){
	
	// create array for checking col
	int colcount[9] = { 0 };

	// loop through the row and check that each integer only occurs once (except for 0)
	for (int rownum = 0; rownum < 9; rownum++){

		// get the int at this spot
		int num = sudoko->puzzle[rownum][col];
		//printf("checking row: %d col: %d, num is %d\n", rownum, col, num);

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
	int *options = find_options(colcount);

	// return the options array if no collisions found
	return options;
}

/*	check_square helper method	*/
int *check_square(sudoku_t *sudoku, int row, int col){

	// variables for the row and column bottom left corner
	int rowcorner;
	int colcorner;

	// array for checking ints in the square
	int squarecount[9] = { 0 };

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

			//printf("checking row: %d col: %d, num is %d\n", x, y, num);

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
	int *options = find_options(squarecount);
	// return the options array if no collisions found
	return options;
}

/*	find_options helper method */
// find the numbers that can go in a particular spot, given the count array
int *find_options(int array[]){
	// initialize an array with all zeros
	int *options = malloc(sizeof(int) * 9);

	// loop through the passed array
	for (int i = 0; i < 9; i++){
		// if any of the indices store 0, add this index to the options array
		if (array[i] == 0){
			options[i] = 1;
		} else {
			options[i] = 0;
		}
	}
	return options;
}

// copies the puzzle from source into the puzzle in dest
void copy_puzzle(sudoku_t *dest, sudoku_t *source) {
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			dest->puzzle[row][col] = source->puzzle[row][col];
		}
	}
}

// Testing code. Run it through the mega gauntlet
#ifdef GAUNTLET

int main() {

	//future test code here

	printf("Testing the sudoku_solve()....\n");
	sudoku_t* puzzle = new_sudoku();
	sudoku_load(puzzle);


	int res = sudoku_solve(puzzle, true);
	if(res == 0){
		fprintf(stdout, "No solutions. \n");
	}
	else if (res == 1){
		fprintf(stdout, "One solution. \n");
	}
	else{
		fprintf(stdout, "Two or more solutions. \n");
	}
	return 0;
}

#endif

#ifdef TESTCREATE
int main() {
	sudoku_t *sudoku = new_sudoku();
	printf("Test random creation");
	sudoku_build(sudoku);
	sudoku_print(sudoku);
	return 0;
}
#endif

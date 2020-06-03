/* 
 * fuzztesing - generate a series of random sudoku puzzles for testing sudoku.c
 * 
 * usage: 
 *   ./fuzztesting numPuzzles
 *
 *  Antony 1, CS 50, May 2020
 */

#include <stdio.h>
#include <stdlib.h> // random, srandom
#include <string.h> // strchr
#include "common/sudokustruct.h"

/* The random() and srandom() functions are provided by stdlib,
 * but for some reason not declared by stdlib.h, so declare here.
 */
long int random(void);

/**************** main ****************/
int main(const int argc, char *argv[])
{
  // check for correct number of parameters
  if(argc != 2){
    fprintf(stderr, "usage: ./fuzztesting numPuzzles\n");
    return 1;
  }
  
  int numPuzzles = atoi(argv[1]);

  //make sure number of generated puzzles is positive
  if(numPuzzles < 0){
    fprintf(stderr, "Error: enter a positive number of puzzles\n");
    return 2;
  }

  
  fprintf(stdout, "\ngenerating %d puzzles \n", numPuzzles);

  // generate random sudoku 
  for (int q = 0; q < numPuzzles; q++){
    sudoku_t* puzzle = new_sudoku();

    //build a random puzzle with 40 empty spaces
    sudoku_build(puzzle, 41);

    //solve the puzzle and print the appropriate output
    sudoku_solve(puzzle, false);
    printf("Solution to the sudoku:\n");
    sudoku_print(puzzle);
    sudoku_delete(puzzle);
  }
  return 0;
}

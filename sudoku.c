/* 
 * sudoku.c - c file for CS50 sudoku module
 * 
 * This file takes a command to create of solve and takes the appropriate action.
 * 
 * Antony 1, CS 50, May 2020
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "sudokustruct.h"


int main(int argc, char *argv[]) {
    if(argc > 3 || argc < 2){
        fprintf(stderr, "usage: ./sudoku gameOption [dificulty]\n");
        return 1;
    }
    if(strcmp(argv[1], "create") == 0){ //then enter create mode
        //parse argv[2] here to get dificulty 

        sudoku_t* puzzle = new_sudoku();
        sudoku_build(puzzle, 10); // arbitrary, left for now
        sudoku_print(puzzle);

        //clean up data structures
        sudoku_delete(puzzle);
    }
    else if(strcmp(argv[1], "solve") == 0){ //then enter solve mode
        sudoku_t* puzzle = new_sudoku();
        sudoku_load(puzzle);
        int res = sudoku_solve(puzzle);
        if(res == 0){
            fprintf(stdout, "No solutions. \n");
        }
        else if (res == 1){
            fprintf(stdout, "One solution. \n");
        }
        else{
            fprintf(stdout, "Two or more solutions. \n");
        }

        //clean up data structures
        sudoku_delete(puzzle);
    }
    else{
        fprintf(stderr, "Error: invalid gameOption. \n");
        return 2;
    }


    
    return 0;
}


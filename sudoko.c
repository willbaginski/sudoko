/* 
 * sudoko.c - c file for CS50 sudoko module
 * 
 * This file takes a command to create of solve and takes the appropriate action.
 * 
 * Antony 1, CS 50, May 2020
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "../common/sudokostruct.h"

int main(int argc, char *argv[]) {
    return 0;
}

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
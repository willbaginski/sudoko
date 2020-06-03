/* 
 * intpair -- struture that holds a pair of ints "row" and "col" (details in intpair.h)
 * 
 * CS50 Spring 2020 Project
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// holds two ints
typedef struct intpair {
    int row;
    int col;
} intpair_t;

intpair_t *new_intpair(int row, int col) {
    intpair_t *intpair = calloc(2, sizeof(int));
    if (intpair == NULL) {  // make sure allocation was successful
        fprintf(stderr, "Error: cannot allocate space for intpair. \n");
        return NULL;
    } else {  // assign the variables and return the intpair
        intpair->row = row;
        intpair->col = col;
        return intpair;
    }
}

int intpair_getRow(intpair_t *intpair) {
    if (intpair == NULL) {
        return -1;
    } else {
        return intpair->row;
    }
}

int intpair_getCol(intpair_t *intpair) {
    if (intpair == NULL) {
        return -1;
    } else {
        return intpair->col;
    }
}

bool intpair_delete(intpair_t *intpair) {
    if (intpair != NULL) {
        free(intpair);
        return true;
    }
    return false;
}
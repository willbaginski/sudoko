/* 
 * intpair -- struture that holds a pair of ints "row" and "col"
 * 
 * CS50 Spring 2020 Project
 */

#include <stdbool.h>

// defines the int pair structure, which holds a pair of ints
// while the structure accepts any int, it only holds ints 0-8 in the sudokustruct module
typedef struct intpair intpair_t;

// creates and returns a new intpair (returns NULL if allocation fails)
intpair_t *new_intpair(int row, int col);

// getter functions for retrieving the ints held by the intpair, return an int
// if the supplied intpair is NULL, return -1
int intpair_getRow(intpair_t *intpair);
int intpair_getCol(intpair_t *intpair);

// deletes a supplied non-NULL intpair
// returns true if it is deleted and false if the intpar passed in is NULL
bool intpair_delete(intpair_t *intpair);
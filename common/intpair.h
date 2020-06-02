/* 
 * intpair -- struture that holds a pair of ints "row" and "col"
 * 
 * CS50 Spring 2020 Project
 */

#include <stdbool.h>

typedef struct intpair intpair_t;

intpair_t *new_intpair(int row, int col);

int intpair_getRow(intpair_t *intpair);
int intpair_getCol(intpair_t *intpair);

bool intpair_delete(intpair_t *intpair);
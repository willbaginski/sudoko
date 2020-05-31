# Test script for the sudoku puzzle
# Authors: Antony 1, Spring 2020

###### Test for bad input to sudoku.c #########

# No args
./sudoku

# Bad args
./sudoku badInput

##### Test for good input to sudoku.c #########

./sudoku solve < ./sudoku create
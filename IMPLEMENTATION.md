# Sudoku Implementation Spec
## Antony 1 - June 2020

## Overview
The 'sudoku' project implements the game of sudoku. Our program includes functionality to build valid sudoku boards of varying difficulties, as well as solve sudoku boards and determine whether a board has no solutions, a single solution, or multiple solutions.

## Different functions and their specs:

### sudoku.c main

The main function in the sudoku module takes two arguments in the following order: a gameOption, and an optional game difficulty. First, the main method checks that there are the correct number of arguments, then it checks if the gameOption given was "create". If so, it looks for a game difficulty argument (if none is provided, it throws an error), and then calls `sudoku_build` and `sudoku_print`, passing `sudoku_build` a the number of squares it should fill in based on the difficulty (more clues/squares for the easier difficulties). If the gameOption given is "solve", the method creates a new sudoku structure, loads the sudoku board passed to stdin into the structure, and then calls `sudoku_solve` on the board. 

### sudokustruct.c sudoku_load method

Purpose: take a formatted sudoku board from stdin and put its contents into a sudoku structure

Pseudocode:

        for row is [0, 9)
            for col is [0, 9)
                check that the current spot in stdin is a number
                    throw error and return false if not
                check that the number is 0-9
                    throw error and return false if not
                add the current number to the corresponding row, col slot in the sudoku board
        return true

### sudokustruct.c build method

Purpose: take an empty sudoku structure and populate it randomly with a given number of clues (filled squares)

Pseudocode:

        check if the board is truly empty
            if not, return false
        seed the random number generator
        construct a solved and full grid
        call remove_squares and pass it the number of empty slots (get by taking 81- clues parameter)
        return true

### sudokustruct.c fill_puzzle method

Purpose: fill an empty sudoku puzzle randomly with a valid full grid (acts as a helper for sudoku_build)

Pseudocode:

        check if the puzzle is full
            if so, return true (base case)
        call get_options on the current row, col in order to find valid entries for the current spot
        determine the number of valid options returned
        if no valid options returned
            free the options array
            return false (we need to backtrack)
        turn the array from get_options into a form which can be more easily iterated
        randomly select an int from the formatted options array and insert it into the current slot in the sudoku board
        get the row and column number for the next slot in the sudoku board
        call fill_puzzle recursively on the next row and col number
        while fill_puzzle returns false
            move on to the next index in the formatted options array
            replace the current value in the puzzle with the next one
            if no more options
                set the current slot to 0
                free allocated space
                return false
        free allocated space
        return true

### sudokustruct.c remove_squares method

Purpose: remove a certain number of slots from a full puzzle randomly so that the final board has a single solution

Pseudocode:

        loop through the sudoku board and check how many slots are empty
        if sudoku_solve on the current board does not return 1 (base case)
            return false
        otherwise if we've reached our removed quota (base case)
            return true
        allocate space for an array with an entry for every filled square
        fill the array with an intpair containing the position of every nonzero/filled slot
        take a random spot from options
        save the spot's value
        remove it from the board
        while sudoku_solve doesn't return 1 or remove_squares returns false
            restore the old value to the current sudoku slot
            get the next nonzero slot from options
            check if we have already tried and failed to find a unique solution for every spot
                delete options
                return false
            get the next row and col from options
            save the value there
            empty this slot in the sudoku puzzle
        delete all intpairs
        return true

### sudokustruct.c sudoku_solve_forwards method

Purpose: solve the given sudoku boards by iterating forwards through it

Pseudocode:

        check if the board is full
            return true if so
        loop through the rows
            loop through the columns
                if the current space is empty
                    loop forwards through all possible values 1-9
                        try placing the current value in this slot
                        if it is valid
                            recursively call sudoku_solve_fowards
                    set the current slot back to zero if we couldn't find a number to place
                    return false
        return false

### sudokustruct.c sudoku_solve_backwards method

Purpose: solve the given sudoku boards by iterating backwards through it (helps to find if there are multiple solutions)

Pseudocode:

        check if the board is full
            return true if so
        loop through the rows
            loop through the columns
                if the current space is empty
                    loop backwards through all possible values 1-9
                        try placing the current value in this slot
                        if it is valid
                            recursively call sudoku_solve_fowards
                    set the current slot back to zero if we couldn't find a number to place
                    return false

### sudokustruct.c sudoku_solve method

Purpose: solve the sudoku board, return the number of solutions

Pseudocode:

        create two empty sudoku boards
        copy the given sudoku board into the two empty sudoku structs
        solve the boards forwards and backwards
        if either solves return false
            delete the two copied sudoku boards
            return 0
        if we're given true as the second parameter
            print the second solved sudoku board
        loop through both solved boards
            if any of the slots are not the same
                delete the two boards
                return 2 (multiple solutions)
        delete both boards
        return 1

### sudokustruct.c check_full method

Purpose: acts as a helper for sudoku_solve, checks if the board is full

Pseudocode:

        loop through the rows
            loop through the columns
                if the current slot is zero, return false
        return true

### sudokustruct.c check_empty method

Purpose: acts as a helper for sudoku_load, checks if the board is empty

Pseudocode:

        loop through the rows
            loop through the columns
                if the current slot is not zero, return false
        return true

### sudokustruct.c sudoku_print method

Purpose: print the given sudoku puzzle to stdout

Pseudocode:

        if the passed board is NULL
            return false
        loop through the rows
            loop through the columns
                print the corresponding slot in the puzzle to stdout, followed by a space
            print a newline char
        return true

### sudokustruct.c sudoku_delete method

Purpose: delete the passed sudoku structure

Pseudocode:

        if the sudoku board passed is not NULL
            free the structure
            return true
        return false

### sudokustruct.c sudoku_validate method

Purpose: check whether there are collisions in the row, column, square of slot provided

Pseudocode:

        if the sudoku board does not exist
            throw an error and return false
        call check_row, check_col, check_square on the current slot
        if any of those returned false
            free any of the valid returned arrays
            return false
        free the returned option arrays
        return true

### sudokustruct.c get_options method

Purpose: check which ints (if any) can go into a given slot (returns in a special format of an array with 9 slots)

Pseudocode:

        if the sudoku board is NULL
            throw an error and return NULL
        call check_row, check_col, check_square and store their returned arrays
        initialize an array for the options
        loop 0-8
            if this int is valid in each of the returned arrays
                this associated int in options array is set to 1
            else
                set this associated int in the options array to 0
        free the three arrays returned by the check methods
        return the options array

### sudokustruct.c check_row method

Purpose: helper method for sudoku_validate and get_options, checks if there are any collisions in the given row and returns an array of the counts for each int in this array

Pseudocode:

        create an array for checking row
        loop through the specified row
            get the int at this spot in the sudoku board
            if the int is not 0
                if the value in the array[int - 1] is not 0
                    return NULL
                increment the corresponding slot's count
        call find_options to translate the array to an options formatted array
        return the options array

### sudokustruct.c check_col method

Purpose: helper method for sudoku_validate and get_options, checks if there are any collisions in the given column and returns an array of the counts for each int in this array

Pseudocode:

        create an array for checking the column
        loop through the specified column
            get the int at this spot in the sudoku board
            if the int is not 0
                if the value in the array[int - 1] is not 0
                    return NULL
                increment the corresponding slot's count
        call find_options to translate the array to an options formatted array
        return the options array

### sudokustruct.c check_square method

Purpose: helper method for sudoku_validate and get_options, checks if there are any collisions in the given square (3x3) and returns an array of the counts for each int in this array

Pseudocode:

        get the row and column numbers for the bottom left corner of the specified square
        create an array for counts in the specified square
        loop through the row values in this square
            loop through the col values in this square
                get the num at this spot in the sudoku board
                if the num is not 0
                    if the value in the array[int - 1] is not 0
                        return NULL
                    increment the corresponding slot's count
        call find_options to translate the array to an options formatted array
        return the options array

### sudokustruct.c find_options method

Purpose: find the numbers that can go into a particular spot, given the count array passed to it

Pseudocode:

        initialize an options array
        loop through the passed array
            if the given element in the passed array is 0
                set the element in the corresponding slot in the options array to 1
            otherwise
                set the element in the corresponding slot in the options array to 0
        return 0

### sudokustruct.c copy_puzzle method

Purpose: copy the given puzzle from a source into a destination structure

Pseudocode:

        loop through the rows in the source
            loop through the columns in the source
                set the corresponding slot in the destination structure to this slot's value in the source

### Notes on structure used

sudoku:

        Defined in sudokustruct.c in the common directory. Is a 2 dimensional array where each array contains 9 slots (for a 9x9 sudoku board).
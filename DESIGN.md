# DESIGN.md for Suduko Final Prohect
## Group Antony 1, CS 50, May 2020

## User interface ##
execute from a command line with usage syntax
* `./sudoku create` to create a random Sudoku puzzle
* `./sudoku solve` to solve a given Sudoku puzzle


## Inputs and Outputs ##
**create:**
input: n/a
output: 9x9 unique, valid suduko grid with 14 empty spaces

**solve:**
input: 9x9 valid suduko grid with spaces
output: 9x9 completed suduko grid

## Functional decomposition into modules ##

### Common Functions

`sudoku_load`- Load a puzzle, in this case, from stdin
`sudoku_build` - Build a new, random sudoku 
`sudoku_solve` - Solve a sudoku that was loaded from `sudoku_load`
`sudoku_print` - Print out the current Sudoku Puzzle
`sudoku_delete`- Free anything in the heap


We anticipate the following modules or functions:

*validate_grid*, which takes a 9x9 partially completed suduko grid and returs a boolean based on if the grid follows Suduko rules


## Pseudo code for logic/algorithmic flow ##
**create:** 

**solve:** 
validates the grid recieved from stdin
runs solving algoritm
returns completed grid



## Dataflow through modules ##

1. *solve* 
2. *create* 


## Major data structures ##

## Testing plan  ##

#!/bin/bash
# Test script for the sudoku puzzle
# Authors: Antony 1, Spring 2020

###### Test for bad input to sudoku.c #########

# No args
./sudoku

# Bad args
./sudoku badInput

# No gameDifficulty
./sudoku create

##### Test for good input to sudoku.c #########
# Test 1
./sudoku solve < common/test1.txt

# Test 2
./sudoku solve < common/test2.txt

# Test 3
./sudoku solve < common/test3.txt

# Testing multiple solution puzzles
./sudoku solve < common/test_multiple_solutions.txt

# Testing with no solutions
./sudoku solve < common/test_no_solutions.txt

# Creating puzzle easy
./sudoku create easy

# Creating puzzle medium
./sudoku create medium

# Creating puzzle hard
./sudoku create hard

# Creating and solving easy
./sudoku create easy | ./sudoku solve

# Creating and solving medium
./sudoku create medium | ./sudoku solve

# Creating and solving hard
./sudoku create hard | ./sudoku solve


##### Test for memory leaks for sudoku.c #########
valgrind --leak-check=full --show-leak-kinds=all ./sudoku create medium  | ./sudoku create medium  
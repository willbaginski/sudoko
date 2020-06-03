# CS50 Sudoku Final Project 
## TESTING.md
### Antony 1, CS50, May 2020

## Testing Process
First, I tried various erroneous queries then I tried valid queries. 

### Testing Improper Input
1 argument
`./querier ../tse-output/letters-depth-1`

3 arguments
`./querier ../tse-output/letters-depth-1 ../tse-output/letters-index-1 ../tse-output/letters-index-1`

starting and
`echo and playground | ./querier ../tse-output/letters-depth-1 ../tse-output/letters-index-1`

starting or
`echo or home | ./querier ../tse-output/letters-depth-1 ../tse-output/letters-index-1`

ending and
`echo home and | ./querier ../tse-output/letters-depth-1 ../tse-output/letters-index-1`

ending or
`echo tse or | ./querier ../tse-output/letters-depth-1 ../tse-output/letters-index-1`

consecutive 'and' 'or' combinations
`echo tse or and playground | ./querier ../tse-output/letters-depth-1 ../tse-output/letters-index-1`

word that doesn't exist
`echo dog | ./querier ../tse-output/letters-depth-1 ../tse-output/letters-index-1`

word combination that doesn't exist
`echo algorithm and tse | ./querier ../tse-output/letters-depth-1 ../tse-output/letters-index-1`

bad charecters
`echo 137 | ./querier ../tse-output/letters-depth-1 ../tse-output/letters-index-1`


### Testing Valid Input
tests on letters-index-1
`cat test1.txt | ./querier ../tse-output/letters-depth-1 ../tse-output/letters-index-1`

tests on letters-index-4
`cat test2.txt | ./querier ../tse-output/letters-depth-4 ../tse-output/letters-index-4`

tests on wikipedia-index-1
`cat test3.txt | ./querier ../tse-output/wikipedia-depth-1 ../tse-output/wikipedia-index-1`

### Testing with FuzzQuery
In order to test with fuzzquery, run `make fuzz` in the command line.
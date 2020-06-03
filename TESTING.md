# CS50 Sudoku Final Project 
## TESTING.md
### Antony 1, CS50, May 2020

## Testing Process
For the `testing.sh`:
First, we tried various erroneous input lines to check our input validation.
Then, we testing the solver on premade sudoku puzzles.
Then, we tested create on *easy*, *medium*, and *hard* mode.
Finally, we testing the create and solve in unison on *easy*, *medium*, and *hard* mode.
We also included a memory leak check on a create and solve command.

For macros testing, we used the following flags:
For `UNITTEST`:

For `CREATETEST`:


* Note: We understand these puzzle do not look randomly generated. This is because our seed relies on time. If you run two create commands separately in your terminal, you will get two random puzzles.

### Testing Improper Input

### Testing Valid Input


### Testing with FuzzQuery
In order to test with fuzztesting, run `make fuzz` in the command line.
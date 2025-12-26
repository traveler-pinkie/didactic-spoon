Skyscrapers
You will implement the solitaire puzzle game known as Skyscrapers (Alternative Website).
Read the rules at the linked web page and try a few easy and medium boards to see how it
can be solved. Your implementation must be able to handle grids as small as 4x4 and as large
as 8x8. Defining all functions in hw1.c is required for this assignment (with the exception of
main functions).
Skyscrapers is a single player puzzle game where the user is given an N x N square board
with the numbers 1-N or spaces occupying every cell. There is also a group of numbers
between 0 and N around the edge of the game board. The numbers in the game board are
meant to represent the height (in floors) of the building that is built on that cell while the
numbers surrounding the game board represent the number of unique buildings that can be
seen from that vantage point. A value of 0 in our implementation means that no clue is being
given about the number of visible buildings for that position.
In the below example the orange number “1” means that a person standing at that location
would only be able to see the red “2” but not the blue “1” because the blue “1” is shorter than
the red “2”. Meanwhile the pink “2” shows that someone standing on the opposite side of the
puzzle would be able to see both the blue “1” and the red “2”. Notice that some of the
surrounding values are 0. This doesn’t mean that there are no visible buildings, but instead
that no clue is being provided about how many buildings are visible from that position.

Part 1: Complete the Implementation of Interactive Skyscrapers
Your implementation must take input from standard input (e.g., using scanf) and display all
output to standard output (e.g., using printf). To facilitate automated grading, input and
output must be formatted exactly as given below. Some scanf and printf commands are
included in the Codespaces Docker image.
Requirement 1A. main() Function in hw1_game.c
A main function has been provided in hw1_game.c that you can change and use to test your
work. The game’s starting state, which includes the size of the board, pieces on the initial
board, and number of visible skyscrapers for each row and column will be provided as
command-line arguments. These can be acquired, respectively, from argv[1], argv[2] and
argv[3]. Use strtoul to convert argv[1] to an integer:
int size = (int)strtoul(argv[1], NULL, 10);
argv[2] provides the starting state as a single string (from left to right, top to bottom) while
argv[3] provides the visible buildings (or keys if you use the variable names from the
template) for the top view (from left to right), bottom view (from left to right), left view (from top
to bottom), and right view (from top to bottom) as a single concatenated string.
For example, for the board shown below:
    1 2
    v v
1 > 2 1 < 2
2 > 1 2 < 1
    ^ ^
    2 1
argv[1] would be 2, argv[2] would be "2112", and argv[3] would be “12211221”.

Assert statements are used to detect unexpected errors and states in a c program. We use the
line assert(argc == 4); to verify that the number of command-line arguments is exactly
what we are expecting. argv[0] is the name of the program itself, therefore we expect 4
values: the program name and 3 input parameters.

Requirement 1B. Implement the Function initialize_board
int initialize_board(const char *initial_state, const char *keys, int
size)

The board game is represented using the board[][] array, as in Homework #0, but this time
the board can be as large as 8x8. Therefore, it is declared as char
board[MAX_LENGTH][MAX_LENGTH], where MAX_LENGTH is 8. initial_state provides
the starting state as a single, row-major ordered, string. keys provides the visible number of
buildings from the outside rows and columns as a single string with the same ordering used in
requirement 1A. The argument size provides the subset of the board[][] array used. For
example, for the board shown below:
    0 0 0 3
    v v v v
0 > 4 - - 2 < 3
2 > 2 - - - < 0
0 > - 2 3 4 < 0
0 > - 4 - - < 0
    ^ ^ ^ ^
    0 1 0 0
size would be 4, initial_state would be “4--22----234-4--” and keys would be
“0003010002003000”.

When initializing the game board, do not modify any characters in board[][] that lie outside
of the bounds. For the example board above, only the 16 characters in rows 0 through 3 and
columns 0 through 3 would be modified.
The return value of this function should identify if this board has already violated one of the two
errors discussed in Requirement 1G or Requirement 1H. A value of 0 should be returned if
either of those errors are encountered and a value of 1 should be returned if the board is
successfully initialized. If initialization fails, then main should end the game with the message:
Invalid initial board state.

Requirement 1C. Print the State of the Game
● The state of the game must be displayed as follows:
    0 0 0 3
    v v v v
0 > 4 - - 2 < 3
2 > 2 - - - < 0
0 > - 2 3 4 < 0
0 > - 4 - - < 0
    ^ ^ ^ ^
    0 1 0 0
● Each symbol must be immediately followed by a space and a new line must be printed
(with no additional spaces) for each new row.
● The upper-left corner is board[0][0] and the lower-right corner is board[3][3 ].

Requirement 1D. Print the Prompts (piece → row → column)
● A prompt message must be formatted exactly as follows (note the space at the end)
Choose a piece (1-4) or q to quit:_
Choose a row (0-3):_
Choose a column (0-3):_
● Do not print a newline character at the end of the message, only the space character.
● After the player has picked three valid sections, check for errors or a winning board.
● If neither condition is met, print the board and request new input.

Requirement 1E. Print an Error Message for Invalid Piece, Row and/or
Column
● If the user attempts to choose an invalid value, print the following prompt message to
request a new section number:
Invalid choice. Choose a piece (1-4) or q to quit:_
Invalid choice. Choose a row (0-3):_
Invalid choice. Choose a column (0-3):_
● Do not print a newline character at the end of the message, only the space character.
● After the player has picked three valid sections, check for errors or a winning board.
● If neither condition is met, print the board and request new input

Requirement 1F. Print an Error Message for Invalid Cell Choice
● If the cell selected already has a token, print the following:
Invalid choice. That space is already occupied.
● Print a newline character at the end of the message.
● Then print the current board state and request new input.

Requirement 1G. Print an Error Message for Attempting to Place a
Duplicate Piece in a Row or Column
● If the cell selected would place the same piece twice in a row or column, print the
following:
Invalid choice. There is already a building with that height in
that row or column.
● Print a newline character at the end of the message.
● Then print the current board state and request new input

Requirement 1H. Print an Error Message for Attempting to Place the last
piece in a row or column that results in an invalid Key.
● If the cell selected would be the last piece for a given row or column but one of the two
key requirements for that row or column is not met, print the following:
Invalid choice. You violate one of the key requirements.
● Print a newline character at the end of the message.
● Then print the current board state and request new input.
● If the errors described in both Requirement 1G and Requirement 1H are met, only
print the Requirement 1G error message.

Requirement 1I. Print the Winning Message
● The winning message is:
Congratulations, you have filled the board!
● Print a newline character at the end of the message.
● Then print the winning board

Part 2: Implement a Skyscrapers Solver

Implement the Function solve
void solve(const char *initial_state, const char *keys, int size)

The solve function takes a pointer to a null-terminated string that describes the board in
row-major order. This means that the first row of the board is given first, followed by the
second row, etc. (The alternative, column-major order, provides the elements of a 2D table one
column at a time.) The argument keys provides a pointer to a null-terminated string that
describes the values of the keys in the same order as the initialize_board function from
part 1. The argument size provides the number of rows and columns in the game board. The
purpose of the solve function is to initialize the global board array with the contents of
initial_state and then attempt to find a solution to the Skyscrapers game on that board.
To solve a given skyscraper problem you must implement 4 heuristics to discover what pieces
need to be placed in which cell. You will NOT be required to implement a backtracking or brute
force solution. An alternative description of these 4 heuristics along with JavaScript code that
implements the solution and suggestions about how to optimize the performance of these
heuristics can be found here: Heuristics 1-3, Heuristic 4.

Heuristic #1: Edge Clue Initialization
If the key value for a given row or column is 1 then that means that the tallest building (N) for
that row or column must be the first visible building. Likewise if the key is N then that means all
buildings must be visible and therefore must be present in the order 1, 2, 3, … N-1, N. We can
extend this technique for other key values as well. We can use the board size, key value, and
distance from the edge to determine if taller buildings are allowed in certain cells. This principle
is called the Edge Constraint Rule. Stated as a rule: On an N * N board, for keys c where 1
< c < N, where d is the distance from the edge counting from zero, we can cross off all
values from N - c + 2 + d up to N, inclusive.

Edge Clue Initialization example:
If our board looks like this:
    2 1 2 4
    v v v v
2 > - - - - < 3
1 > - - - - < 3
3 > - - - - < 2
3 > - - - - < 1
    ^ ^ ^ ^
    2 4 2 1

Then let’s walk through what the edge clue initialization and the edge constraint rule tells us
about column 1 and column 2:

1 2
v v
- -
- -
- -
- -
^ ^
4 2

Because the top key for column 1 is a “1”, it means that there must be the value N at row = 0,
column = 1.

1 2
v v
4 -
- -
- -
- -
^ ^
4 2

Because the bottom key for column 1 is a “4” which == size, it means that the values from
bottom to top on column 1 must be 1-4 in ascending order.

1 2
v v
4 -
3 -
2 -
1 -
^ ^
4 2

On column 2 we don’t have a key value of either 1 or 4 so we must apply the edge constraint
rule which is to cross off all values from N - c + 2 + d up to N, inclusive. In this case N=4,
c = 2. This means that neither row 0 nor row 3 of column 2 can contain “4” (4-2+2-0 == 4). This
doesn’t help us place a piece directly but it enables us to begin a process of elimination for
where certain values can be placed. It would be a good idea to create a data structure that
keeps track of what all the valid options are for each cell (referred to as a “constraint
list” in the attached blog post). We should also be checking to see if only one value is
valid for a given cell and then populating that value in the main board.

Edge Constraint Rule (Derivation and Explanation)

We are given a 0-index array of size N.

Let c be the target value of visible buildings that we want to be able to see.

In this explanation, let N = 5 and c = 4.

Below is a visualization of the array, where d is the index of each position in the array

d 0 1 2 3 4

Let x be the height of the building that we're going to place. We can pick any index to place our
building at.

However, when we place our building, we need to make sure that it is possible to hit the target
value c. Therefore, we need to calculate the maximum possible visible building if we decide to
place a building of height x at index d.

Below is the formula for the maximum possible visible buildings when we place a building of
height x at index d (the equation may overcount, but if it yields a number lower than c, we
know that it definitely can't satisfy the condition and thus be eliminated):

d + (N - x) + 1

- d is the number of buildings that can be placed before our building. For example, if we
decided to place our building at index 3, then there are 3 buildings before it. We assume
that we can see all of these buildings (by placing all the smaller buildings in ascending
order before our building).

- N - x is the number of buildings that are taller than the building we're going to place.
This accounts for how many buildings can be visible behind the building we placed. We
assume that we can see all of those buildings as well (by placing them in ascending
order behind our building).

- The 1 accounts for the building we placed.
Essentially, d counts the buildings before, and N - x counts the buildings after the building with
height of x that is placed at index d.
This value must be greater than or equal to our target value c, otherwise, it will be impossible
to hit our target value. Thus, we have the following inequality

c <= d + (N - x) + 1

Now let's isolate x to see what its valid values can be.

N - c + d + 1 > x

Since the height of the building starts at 1, we must normalize the inequality by adding 1 to the
left side, thus giving us the final result:

N - c + d + 2 > x

The height of the building at each cell must satisfy this requirement for the top, bottom, left,
and right constraints.

Heuristic #2: Constraint Propagation

Now that we have made some assertions based on the key value of our board, it is time to use
the fact that the same value cannot appear twice in a given row or column to make more
assertions. Once we know that row 0, column 2 in the below example is the value “4” we know
that all other values in row 0 and all other values in column 2 cannot be “4”. We should
traverse the “constraints list” data structure and remove “4” from the other entries in row 0 and
column 2. While we are doing this, we should also identify if there are any cells in our
constraints list that only have one potential value and add them to the board (and perform
constraint propagation on that cell’s row and column).

Heuristic #3: Process of Elimination
Now that we have a list of all the possible values for each cell we can identify any values that
only appear once in a given row or column. The below example shows that the value “4” in row
1 is only present in the cell in column 1. You will also notice that in column 3 the value “4” can
only appear in row 3. This means that both cell (1,1) and (3,3) must have value “4”. We can
then use this new information to continue applying heuristic #2 (Constraint Propagation) in the
hopes that we will be able to solve the whole board.

Part 3: Heuristic #4: Clue Elimination
You will note that we have only used our key values so far to eliminate large values from
appearing near the edge but we do not have a strategy for checking if there are limited building
placement options that would satisfy the key requirements across a row or column. This
process which we will call “Sequence Filtration” looks at all possible values across a row or a
column that are still allowed based on our “constraints list” and determines if any cell values
are forced based on a key for that row or column.
Let’s look at the following example:

only appear in row 3. This means that both cell (1,1) and (3,3) must have value “4”. We can
then use this new information to continue applying heuristic #2 (Constraint Propagation) in the
hopes that we will be able to solve the whole board.
Part 3: Heuristic #4: Clue Elimination
You will note that we have only used our key values so far to eliminate large values from
appearing near the edge but we do not have a strategy for checking if there are limited building
placement options that would satisfy the key requirements across a row or column. This
process which we will call “Sequence Filtration” looks at all possible values across a row or a
column that are still allowed based on our “constraints list” and determines if any cell values
are forced based on a key for that row or column.
Let’s look at the following example:

In this column we know that the top key is a “2” and the number “4” appears in row 3. Our
constraints list doesn’t give us any information about which of the top 3 rows contains the “1”,
the “2”, or the “3” and so there are 6 possible ways this column could be set.

Reading from top to bottom these are the 6 sequences that we need to consider with the
respective key value that would be required to make that sequence a valid solution to the
column.

1-3-2-4 (3) we would see 1-3-4
1-2-3-4 (4) we would see 1-2-3-4
2-3-1-4 (3) we would see 2-3-4
2-1-3-4 (3) we would see 2-3-4
3-2-1-4 (2) we would see 3-4
3-1-2-4 (2) we would see 3-4

We now know that only the last 2 sequences match the required key for this column. That
means we know that row 0 must contain the “3”. (This will not tell us whether row 1 and 2 are
“1”-”2” or “2”-”1” though)

The other benefit that clue elimination with sequence filtration gives us is that occasionally we
won't discover the value for a cell but we will discover that no sequence with a valid key has a
certain value in a certain cell. To demonstrate this look at the row 1 from the right hand side:

Reading from top to bottom these are the 6 sequences that we need to consider with the
respective key value that would be required to make that sequence a valid solution to the
column.
1-3-2-4 (3) we would see 1-3-4
1-2-3-4 (4) we would see 1-2-3-4
2-3-1-4 (3) we would see 2-3-4
2-1-3-4 (3) we would see 2-3-4
3-2-1-4 (2) we would see 3-4
3-1-2-4 (2) we would see 3-4
We now know that only the last 2 sequences match the required key for this column. That
means we know that row 0 must contain the “3”. (This will not tell us whether row 1 and 2 are
“1”-”2” or “2”-”1” though)
The other benefit that clue elimination with sequence filtration gives us is that occasionally we
won't discover the value for a cell but we will discover that no sequence with a valid key has a
certain value in a certain cell. To demonstrate this look at the row 1 from the right hand side:
There are 6 sequences available for this row with right hand key values in parenthesis next to
them:
1-4-2-3 (2)
1-4-3-2 (3)
2-4-1-3 (2)
2-4-3-1 (3)
3-4-1-2 (2)
3-4-2-1 (3)

Of these sequences 3 of them meet the key requirements and no one value is guaranteed
based on the viable sequences, but it is worth noting that in the three viable sequences, value
“3” never appears in column 2 and value “1” never appears in column 3. This means that we
can eliminate these values from the “constraints list”.
Sequence Filtration (Clue Elimination) Time Complexity Problems:
Since we are dealing with permutations in generating our sequences the time complexity of
computing every valid sequence is O(N!). This is unlikely to be practical for N values larger
than 4 or 5. One strategy that mimics how humans would solve this problem would be to sort
the rows and columns to be considered by Sequence Filtration not by their index number
(doing row 0 first, then row 1, etc…) but by the number of unplaced cells in that given row or
column. This should ensure that we check only rows and columns that are already close to
being solved and reduce our complexity to O(k!) where k is the number of remaining cells in a
given row or column.
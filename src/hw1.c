#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "hw1.h"

int top_key[MAX_LENGTH] = {0};
int bottom_key[MAX_LENGTH] = {0};
int left_key[MAX_LENGTH] = {0};
int right_key[MAX_LENGTH] = {0};

char board[MAX_LENGTH][MAX_LENGTH] = {0};

int boardSzie;
int checkStatus();

int check_dupes_col(char choice, int col)
{
    for (int i = 0; i < boardSzie; i++)
    {
        if (board[i][col] == choice)
        {
            return 0;
        }
    }
    return 1;
}

int check_dupes_row(char choice, int row)
{
    for (int i = 0; i < boardSzie; i++)
    {
        if (board[row][i] == choice)
        {
            return 0;
        }
    }
    return 1;
}

int checkStatus()
{
    for (int i = 0; i < boardSzie; ++i)
    {
        for (int j = 0; j < boardSzie; ++j)
        {
            if(board[i][j]=='-'){return 0;}
        }
    }
    return 1;
}

int is_last_piece(int row, int col)
{
    int row_count = 0;
    int col_count = 0;

    for (int i = 0; i < boardSzie; i++)
    {
        if (board[row][i] == '-') row_count++;
        if (board[i][col] == '-') col_count++;
    }

    return (row_count == 1 || col_count == 1);
}

int initialize_board(const char *initial_state, const char *keys, int size)
{
    (void)initial_state;
    (void)keys;
    (void)size;
    boardSzie = size;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            board[i][j] = initial_state[i * size + j];
        }
    }

    for (int i = 0; i < size; i++)
    {
        top_key[i] = keys[i] - '0';
    }

    for (int i = size; i < 2 * size; i++)
    {
        bottom_key[i - size] = keys[i] - '0';
    }

    for (int i = 2 * size; i < 3 * size; i++)
    {
        left_key[i - 2 * size] = keys[i] - '0';
    }

    for (int i = 3 * size; i < 4 * size; i++)
    {
        right_key[i - 3 * size] = keys[i] - '0';
    }

    return 1;
}

int solve(const char *initial_state, const char *keys, int size)
{
    (void)initial_state;
    (void)keys;
    (void)size;

    return 1;
}

void print_board(int size)
{
    (void)size;

    printf("    ");
    for (int i = 0; i < size; ++i)
    {
        printf("%d ", top_key[i]);
    }
    printf("\n    ");
    for (int i = 0; i < size; ++i)
    {
        printf("v ");
    }
    printf("\n");

    for (int i = 0; i < size; ++i)
    {
        printf("%d > ", left_key[i]);
        for (int j = 0; j < size; ++j)
        {

            printf("%c ", board[i][j]);
        }
        printf("< %d\n", right_key[i]);
    }

    printf("    ");
    for (int i = 0; i < size; ++i)
    {
        printf("^ ");
    }
    printf("\n    ");
    for (int i = 0; i < size; ++i)
    {
        printf("%d ", bottom_key[i]);
    }
    printf("\n");
}

int get_move()
{
    char var;
    int rowNum;
    int colNum;

    printf("Choose a piece (1-%d) or q to quit: ", boardSzie);
    scanf(" %c", &var);

    while ((var < '1' || var > '5') && var != 'q')
    {
        printf("Invalid choice. Choose a piece (1-%d) or q to quit: ", boardSzie);
        scanf(" %c", &var);
    }

    if (var == 'q')
    {
        return 1;
    }

    printf("Choose a row (0-%d): ", boardSzie-1);
    scanf("%d", &rowNum);

    while (rowNum < 0 || rowNum > 4)
    {
        printf("Invalid choice. Choose a row (0-%d): ", boardSzie-1);
        scanf("%d", &rowNum);
    }

    printf("Choose a column (0-%d): ", boardSzie-1);
    scanf("%d", &colNum);

    while (colNum < 0 || colNum > 4)
    {
        printf("Invalid choice. Choose a column (0-%d): ", boardSzie-1);
        scanf("%d", &colNum);
    }
    if(try_move(var, rowNum, colNum) == 1){
        print_board(boardSzie);
        return 0;
    }else{
        return 1;
    }
}

int try_move(char choice, int row, int col)
{
    if (board[row][col] != '-')
    {
        printf("Invalid choice. That space is already occupied.\n\n");
        print_board(boardSzie);
    }
    else if (check_dupes_row(choice, row) == 0 || check_dupes_col(choice, col) == 0)
    {
        printf("Invalid choice. There is already a building with that height in that row or column.\n\n");
        print_board(boardSzie);
    }
    else if (is_last_piece(row, col))
    {
        printf("Invalid choice. You violate one of the key requirements.\n\n");
        print_board(boardSzie);
    }
    else
    {
        board[row][col] = choice;
        if (checkStatus() == 1)
        {
            printf("Congratulations, you have filled the board!\n");
            print_board(boardSzie);
            return 0;
        }
    }
    return 1;
}




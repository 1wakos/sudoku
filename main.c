#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 16

int board[MAX_SIZE][MAX_SIZE];

// initialize the sudoku board to 0s
void initializeBoard(int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            board[i][j] = 0;
        }
    }
}

// print the Sudoku board
void printBoard(int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (board[i][j] == 0)
            {
                printf(". ");
            }
            else
            {
                printf("%d ", board[i][j]);
            }
        }
        printf("\n");
    }
}

// check if num is unused in a given row
int unUsedInRow(int size, int row, int num)
{
    for (int col = 0; col < size; col++)
    {
        if (board[row][col] == num)
        {
            return 0;
        }
    }
    return 1;
}

// check if num is unused in a given column
int unUsedInCol(int size, int col, int num)
{
    for (int row = 0; row < size; row++)
    {
        if (board[row][col] == num)
        {
            return 0;
        }
    }
    return 1;
}

// check if num is unused in a 3x3 box
int unUsedInBox(int rowStart, int colStart, int num)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[rowStart + i][colStart + j] == num)
            {
                return 0;
            }
        }
    }
    return 1;
}

// check if it is safe to put num in board[row][col]
int checkIfSafe(int size, int row, int col, int num)
{
    return unUsedInRow(size, row, num) &&
           unUsedInCol(size, col, num) &&
           unUsedInBox(row - row % 3, col - col % 3, num);
}

// fill a 3x3 box starting at (rowStart, colStart)
void fillBox(int rowStart, int colStart)
{
    int num;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            do
            {
                num = rand() % 9 + 1;
            } while (!unUsedInBox(rowStart, colStart, num));
            board[rowStart + i][colStart + j] = num;
        }
    }
}

// fill diagonal 3x3 boxes
void fillDiagonal()
{
    for (int i = 0; i < 9; i += 3)
    {
        fillBox(i, i);
    }
}

// recursively fill remaining cells
int fillRemaining(int i, int j)
{
    if (i == 9)
    {
        return 1;
    }
    if (j == 9)
    {
        return fillRemaining(i + 1, 0);
    }
    if (board[i][j] != 0)
    {
        return fillRemaining(i, j + 1);
    }

    for (int num = 1; num <= 9; num++)
    {
        if (checkIfSafe(9, i, j, num))
        {
            board[i][j] = num;
            if (fillRemaining(i, j + 1))
            {
                return 1;
            }
            board[i][j] = 0;
        }
    }

    return 0;
}

int main()
{
    srand(time(0));
    printf("sudoku\n");

    int size = 9;
    initializeBoard(size);
    fillDiagonal();
    fillRemaining(0, 0);
    printBoard(size);

    return 0;
}
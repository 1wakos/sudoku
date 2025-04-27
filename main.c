#include <stdio.h>
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

// print the sudoku board
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

int main()
{
    printf("sudoku\n");

    int size = 9;
    initializeBoard(size);
    printBoard(size);

    return 0;
}

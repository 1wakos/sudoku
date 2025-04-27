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

int main()
{
    printf("sudoku\n");

    int size = 9;
    initializeBoard(size);
    printBoard(size);

    return 0;
}

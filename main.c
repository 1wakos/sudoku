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

int main()
{
    printf("sudoku\n");

    int size = 9;
    initializeBoard(size);

    return 0;
}

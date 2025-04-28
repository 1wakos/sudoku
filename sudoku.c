#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Sudoku *createSudoku(int size)
{
    Sudoku *sudoku = malloc(sizeof(Sudoku));
    if (!sudoku)
    {
        return NULL;
    }
    sudoku->size = size;

    if (size == 4)
        sudoku->boxSize = 2;
    else if (size == 9)
        sudoku->boxSize = 3;
    else
        sudoku->boxSize = 4;

    sudoku->board = malloc(size * sizeof(int *));
    if (!sudoku->board)
    {
        free(sudoku);
        return NULL;
    }
    for (int i = 0; i < size; i++)
    {
        sudoku->board[i] = calloc(size, sizeof(int));
        if (!sudoku->board[i])
        {
            // free previously allocated rows
            for (int j = 0; j < i; j++)
                free(sudoku->board[j]);
            free(sudoku->board);
            free(sudoku);
            return NULL;
        }
    }
    return sudoku;
}

void freeSudoku(Sudoku *sudoku)
{
    if (!sudoku)
        return;
    for (int i = 0; i < sudoku->size; i++)
    {
        free(sudoku->board[i]);
    }
    free(sudoku->board);
    free(sudoku);
}

// --- FUNCTIONS IMPLEMENTATION ---

// initialize the sudoku board to 0s
void initializeBoard(Sudoku *sudoku)
{
    for (int i = 0; i < sudoku->size; i++)
    {
        for (int j = 0; j < sudoku->size; j++)
        {
            sudoku->board[i][j] = 0;
        }
    }
}

// print the sudoku board
void printBoard(const Sudoku *sudoku)
{
    printf("\n");
    for (int i = 0; i < sudoku->size; i++)
    {
        for (int j = 0; j < sudoku->size; j++)
        {
            if (sudoku->board[i][j] != 0)
                printf("%d ", sudoku->board[i][j]);
            else
                printf(". ");
        }
        printf("\n");
    }
}

// check if num is unused in a given row
int unUsedInRow(const Sudoku *sudoku, int row, int num)
{
    for (int col = 0; col < sudoku->size; col++)
    {
        if (sudoku->board[row][col] == num)
            return 0;
    }
    return 1;
}

// check if num is unused in a given column
int unUsedInCol(const Sudoku *sudoku, int col, int num)
{
    for (int row = 0; row < sudoku->size; row++)
    {
        if (sudoku->board[row][col] == num)
            return 0;
    }
    return 1;
}

// check if num is unused in a 3x3 box
int unUsedInBox(const Sudoku *sudoku, int rowStart, int colStart, int num)
{
    for (int i = 0; i < sudoku->boxSize; i++)
    {
        for (int j = 0; j < sudoku->boxSize; j++)
        {
            if (sudoku->board[rowStart + i][colStart + j] == num)
                return 0;
        }
    }
    return 1;
}

// check if it is safe to put num in board[row][col]
int checkIfSafe(const Sudoku *sudoku, int row, int col, int num)
{
    return unUsedInRow(sudoku, row, num) &&
           unUsedInCol(sudoku, col, num) &&
           unUsedInBox(sudoku, row - row % sudoku->boxSize, col - col % sudoku->boxSize, num);
}

// fill a 3x3 box starting at (rowStart, colStart)
void fillBox(Sudoku *sudoku, int rowStart, int colStart)
{
    int num;
    for (int i = 0; i < sudoku->boxSize; i++)
    {
        for (int j = 0; j < sudoku->boxSize; j++)
        {
            do
            {
                num = rand() % sudoku->size + 1;
                // repeat if the number is already used inside this box
            } while (!unUsedInBox(sudoku, rowStart, colStart, num));
            // place the number into the correct position inside the box
            sudoku->board[rowStart + i][colStart + j] = num;
        }
    }
}

// fill diagonal 3x3 boxes
void fillDiagonal(Sudoku *sudoku)
{
    for (int i = 0; i < sudoku->size; i += sudoku->boxSize)
    {
        fillBox(sudoku, i, i);
    }
}

// recursively fill remaining cells
int fillRemaining(Sudoku *sudoku, int i, int j)
{
    if (i == sudoku->size)
        return 1;

    // if we reach the end of a row, move to the next row
    if (j == sudoku->size)
        return fillRemaining(sudoku, i + 1, 0);
    // skip cells that are already filled (like diagonal boxes)
    if (sudoku->board[i][j] != 0)
        return fillRemaining(sudoku, i, j + 1);

    for (int num = 1; num <= sudoku->size; num++)
    {
        if (checkIfSafe(sudoku, i, j, num))
        {
            sudoku->board[i][j] = num;
            if (fillRemaining(sudoku, i, j + 1))
                return 1;
            sudoku->board[i][j] = 0;
        }
    }
    return 0;
}

// remove k digits randomly to create a puzzle
void removeKDigits(Sudoku *sudoku, int k)
{
    while (k > 0)
    {
        // pick a random cell index
        int cellId = rand() % (sudoku->size * sudoku->size);
        int i = cellId / sudoku->size; // calculate row
        int j = cellId % sudoku->size; // calculate column
        if (sudoku->board[i][j] != 0)
        {
            sudoku->board[i][j] = 0;
            k--;
        }
    }
}

void generateSudoku(int size, int difficulty)
{
    Sudoku *sudoku = createSudoku(size);

    int boxSize;
    if (size == 4)
        boxSize = 2;
    else if (size == 9)
        boxSize = 3;
    else
        boxSize = 4;

    initializeBoard(sudoku);
    fillDiagonal(sudoku);
    fillRemaining(sudoku, 0, 0);

    int k;
    if (difficulty == 1)
        k = size * size / 4; // easy
    else if (difficulty == 2)
        k = size * size / 3; // medium
    else
        k = size * size / 2; // hard

    removeKDigits(sudoku, k);

    // generating the board

    freeSudoku(sudoku);
}

// save the current game to a file
void saveGame(const Sudoku *sudoku, const char *filename)
{
    FILE *fp = fopen(filename, "w");
    if (!fp)
    {
        printf("Error saving game!\n");
        return;
    }
    fprintf(fp, "%d\n", sudoku->size);
    for (int i = 0; i < sudoku->size; i++)
    {
        for (int j = 0; j < sudoku->size; j++)
        {
            fprintf(fp, "%d ", sudoku->board[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    printf("Game saved successfully!\n");
}

// load a saved game from a file
Sudoku *loadGame(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        printf("No saved game found...\n");
        return NULL;
    }
    int size;
    fscanf(fp, "%d", &size);

    Sudoku *sudoku = createSudoku(size);
    if (!sudoku)
    {
        fclose(fp);
        return NULL;
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            fscanf(fp, "%d", &sudoku->board[i][j]);
        }
    }
    fclose(fp);
    return sudoku;
}

// allow player to input a move
void playerMove(Sudoku *sudoku)
{
    int row, col, num;

    printf("Enter row (0-%d), column (0-%d), and number (1-%d): ", sudoku->size - 1, sudoku->size - 1, sudoku->size);
    int result = scanf("%d %d %d", &row, &col, &num); // if num is correct
    if (result != 3)
    {
        printf("Invalid input! Please enter three integers (row, column, number).\n");
        while (getchar() != '\n')
            ;
        return;
    }

    // if nums are in range
    if (row >= 0 && row < sudoku->size && col >= 0 && col < sudoku->size && num >= 1 && num <= sudoku->size)
    {
        if (checkIfSafe(sudoku, row, col, num))
        {
            sudoku->board[row][col] = num; // save num
            printf("Correct move!\n");
        }
        else
        {
            printf("Invalid move! The number cannot be placed here:(\n");
        }
    }
    else
    {
        printf("Invalid input! Row, column, or number out of bounds.\n");
    }
    printBoard(sudoku);
}

// allow player to delete a move
void deleteMove(Sudoku *sudoku)
{
    int row, col;
    printf("Enter row (0-%d) and column (0-%d) to delete: ", sudoku->size - 1, sudoku->size - 1);
    scanf("%d %d", &row, &col);

    if (row >= 0 && row < sudoku->size && col >= 0 && col < sudoku->size)
    {
        if (sudoku->board[row][col] != 0)
        {
            sudoku->board[row][col] = 0;
            printf("Value deleted.\n");
        }
        else
        {
            printf("Cell already empty!\n");
        }
    }
    else
    {
        printf("Invalid input!\n");
    }
}

// check if the board is completely filled
int checkWin(const Sudoku *sudoku)
{
    for (int i = 0; i < sudoku->size; i++)
    {
        for (int j = 0; j < sudoku->size; j++)
        {
            if (sudoku->board[i][j] == 0)
            {
                return 0; // not finished yet
            }
        }
    }
    return 1; // board filled
}

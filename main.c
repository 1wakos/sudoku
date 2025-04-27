#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 16

int board[MAX_SIZE][MAX_SIZE];
int currentSize = 9;

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
    printf("\n");
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
int unUsedInBox(int boxSize, int rowStart, int colStart, int num)
{
    for (int i = 0; i < boxSize; i++)
    {
        for (int j = 0; j < boxSize; j++)
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
int checkIfSafe(int size, int boxSize, int row, int col, int num)
{
    return unUsedInRow(size, row, num) &&
           unUsedInCol(size, col, num) &&
           unUsedInBox(boxSize, row - row % boxSize, col - col % boxSize, num);
}

// fill a 3x3 box starting at (rowStart, colStart)
void fillBox(int boxSize, int rowStart, int colStart, int size)
{
    int num;
    for (int i = 0; i < boxSize; i++)
    {
        for (int j = 0; j < boxSize; j++)
        {
            do
            {
                num = rand() % size + 1;
            } while (!unUsedInBox(boxSize, rowStart, colStart, num));
            board[rowStart + i][colStart + j] = num;
        }
    }
}

// fill diagonal 3x3 boxes
void fillDiagonal(int size, int boxSize)
{
    for (int i = 0; i < size; i += boxSize)
    {
        fillBox(boxSize, i, i, size);
    }
}

// recursively fill remaining cells
int fillRemaining(int size, int boxSize, int i, int j)
{
    if (i == size)
    {
        return 1;
    }
    if (j == size)
    {
        return fillRemaining(size, boxSize, i + 1, 0);
    }
    if (board[i][j] != 0)
    {
        return fillRemaining(size, boxSize, i, j + 1);
    }

    for (int num = 1; num <= size; num++)
    {
        if (checkIfSafe(size, boxSize, i, j, num))
        {
            board[i][j] = num;
            if (fillRemaining(size, boxSize, i, j + 1))
            {
                return 1;
            }
            board[i][j] = 0;
        }
    }

    return 0;
}

// remove k digits randomly to create a puzzle
void removeKDigits(int size, int k)
{
    while (k > 0)
    {
        int cellId = rand() % (size * size);
        int i = cellId / size;
        int j = cellId % size;
        if (board[i][j] != 0)
        {
            board[i][j] = 0;
            k--;
        }
    }
}

void generateSudoku(int size, int difficulty)
{
    int boxSize = (size == 4) ? 2 : (size == 9) ? 3
                                                : 4;

    initializeBoard(size);
    fillDiagonal(size, boxSize);
    fillRemaining(size, boxSize, 0, 0);

    int k;
    if (difficulty == 1)
        k = size * size / 4; // easy
    else if (difficulty == 2)
        k = size * size / 3; // medium
    else
        k = size * size / 2; // hard

    removeKDigits(size, k);
}

// save the current game to a file
void saveGame(int size)
{
    FILE *fp = fopen("sudoku_save.txt", "w");
    if (!fp)
    {
        printf("error saving game!\n");
        return;
    }
    fprintf(fp, "%d\n", size);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            fprintf(fp, "%d ", board[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    printf("game saved successfully!\n");
}

// load a saved game from a file
void loadGame()
{
    FILE *fp = fopen("sudoku_save.txt", "r");
    if (!fp)
    {
        printf("no saved game found...\n");
        return;
    }
    fscanf(fp, "%d", &currentSize);
    for (int i = 0; i < currentSize; i++)
    {
        for (int j = 0; j < currentSize; j++)
        {
            fscanf(fp, "%d", &board[i][j]);
        }
    }
    fclose(fp);
    printf("game loaded successfully!\n");
    printBoard(currentSize);
}

// allow player to input a move
void playerMove(int size)
{
    int row, col, val;
    printf("Enter row (0-%d), column (0-%d), and value (1-%d): ", size - 1, size - 1, size);
    scanf("%d %d %d", &row, &col, &val);

    if (row >= 0 && row < size && col >= 0 && col < size && val >= 1 && val <= size)
    {
        if (board[row][col] == 0)
        {
            board[row][col] = val;
        }
        else
        {
            printf("Cell already filled. Choose another one!\n");
        }
    }
    else
    {
        printf("Invalid input!\n");
    }
}

// allow player to delete a move
void deleteMove(int size)
{
    int row, col;
    printf("Enter row (0-%d) and column (0-%d) to delete: ", size - 1, size - 1);
    scanf("%d %d", &row, &col);

    if (row >= 0 && row < size && col >= 0 && col < size)
    {
        if (board[row][col] != 0)
        {
            board[row][col] = 0;
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

void menu()
{
    int choice;
    int difficulty = 1;

    do
    {
        printf("\n--- Sudoku Menu ---\n");
        printf("1. New Game\n");
        printf("2. Choose Board Size (4x4, 9x9, 16x16)\n");
        printf("3. Choose Difficulty (1 - Easy, 2 - Medium, 3 - Hard)\n");
        printf("4. Save Game\n");
        printf("5. Load Game\n");
        printf("6. Make a Move\n");
        printf("7. Delete a Move\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            generateSudoku(currentSize, difficulty);
            printBoard(currentSize);
        }
        else if (choice == 2)
        {
            printf("Choose size (4, 9, 16): ");
            scanf("%d", &currentSize);
            if (currentSize != 4 && currentSize != 9 && currentSize != 16)
            {
                printf("Invalid size. Setting to 9x9.\n");
                currentSize = 9;
            }
        }
        else if (choice == 3)
        {
            printf("Choose difficulty (1 - Easy, 2 - Medium, 3 - Hard): ");
            scanf("%d", &difficulty);
            if (difficulty < 1 || difficulty > 3)
            {
                printf("Invalid difficulty. Setting to Easy.\n");
                difficulty = 1;
            }
        }
        else if (choice == 4)
        {
            saveGame(currentSize);
        }
        else if (choice == 5)
        {
            loadGame();
        }
        else if (choice == 6)
        {
            playerMove(currentSize);
            printBoard(currentSize);
        }
        else if (choice == 7)
        {
            deleteMove(currentSize);
            printBoard(currentSize);
        }
        else if (choice == 8)
        {
            printf("Exiting the game. Goodbye!\n");
        }
        else
        {
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 8);
}

int main()
{
    srand(time(0));
    menu();
    return 0;
}
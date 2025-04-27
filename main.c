#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sudoku.h"

// user menu
void menu()
{
    Sudoku *sudoku = NULL;
    int difficulty = 1;
    int choice;

    do
    {
        printf("\n--- Sudoku Menu ---\n");
        printf("1. New Game\n");
        printf("2. Load Game\n");
        printf("3. Save Game\n");
        printf("4. Print Board\n");
        printf("5. Exit\n");
        printf("6. Player Move\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            if (sudoku)
                freeSudoku(sudoku);
            int size;
            printf("Enter board size (4x4, 9x9, or 16x16): ");
            scanf("%d", &size);
            if (size != 4 && size != 9 && size != 16)
                size = 9;

            sudoku = createSudoku(size);
            if (!sudoku)
            {
                printf("Failed to allocate memory!\n");
                exit(1);
            }
            fillDiagonal(sudoku);
            fillRemaining(sudoku, 0, 0);

            printf("Choose difficulty (1 - Easy, 2 - Medium, 3 - Hard): ");
            scanf("%d", &difficulty);
            int k = (difficulty == 1) ? size * size / 4 : (difficulty == 2) ? size * size / 3
                                                                            : size * size / 2;
            removeKDigits(sudoku, k);
        }
        else if (choice == 2)
        {
            if (sudoku)
                freeSudoku(sudoku);
            sudoku = loadGame("sudoku_save.txt");
        }
        else if (choice == 3)
        {
            if (sudoku)
                saveGame(sudoku, "sudoku_save.txt");
            else
                printf("No game to save!\n");
        }
        else if (choice == 4)
        {
            if (sudoku)
                printBoard(sudoku);
            else
                printf("No game loaded!\n");
        }
        else if (choice == 6)
        {
            if (sudoku)
                playerMove(sudoku);
            else
                printf("No game loaded!\n");
        }
    } while (choice != 5);

    if (sudoku)
        freeSudoku(sudoku);
}

int main()
{
    srand(time(NULL));
    menu();
    return 0;
}

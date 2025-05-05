#include "sudoku.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

void menu()
{
    Sudoku *sudoku = NULL;
    int difficulty = 1;
    int choice;
    time_t startTime = 0, endTime = 0; // zmienne na czas gry

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
            int k;
            if (difficulty == 1)
            {
                k = size * size / 4;
            }
            else if (difficulty == 2)
            {
                k = size * size / 3;
            }
            else
            {
                k = size * size / 2;
            }

            removeKDigits(sudoku, k);

            startTime = time(NULL); // start time for the game
        }
        else if (choice == 2)
        {
            if (sudoku)
                freeSudoku(sudoku);
            sudoku = loadGame("sudoku_save.txt");
            startTime = time(NULL); // start counting after loading
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

    endTime = time(NULL);                           // save the duration of the game
    double duration = difftime(endTime, startTime); // in seconds
    printf("\nGame duration: %.0f seconds.\n", duration);
}

int main() {
    menu();
    return 0;
}

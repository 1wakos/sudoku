#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sudoku.h"

// user menu
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
            if (checkWin(currentSize))
            {
                printf("CONGRATULATIONS!!!!!!! You completed the Sudoku:)\n");
                break;
            }
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
            printf("Invalid choice. Please try again!\n");
        }
    } while (choice != 8);
}

int main()
{
    srand(time(0));
    menu();
    return 0;
}
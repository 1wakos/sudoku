#ifndef SUDOKU_H
#define SUDOKU_H

#define MAX_SIZE 16

extern int board[MAX_SIZE][MAX_SIZE];
extern int currentSize;

void initializeBoard(int size);
void printBoard(int size);
void generateSudoku(int size, int difficulty);
void saveGame(int size);
void loadGame();
void playerMove(int size);
void deleteMove(int size);
int checkWin(int size);

#endif
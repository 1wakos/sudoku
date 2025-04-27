#ifndef SUDOKU_H
#define SUDOKU_H

typedef struct
{
    int **board;
    int size;
    int boxSize;
} Sudoku;

Sudoku *createSudoku(int size);
void freeSudoku(Sudoku *sudoku);

void initializeBoard(Sudoku *sudoku);
void printBoard(const Sudoku *sudoku);

int unUsedInRow(const Sudoku *sudoku, int row, int num);
int unUsedInCol(const Sudoku *sudoku, int col, int num);
int unUsedInBox(const Sudoku *sudoku, int rowStart, int colStart, int num);
int checkIfSafe(const Sudoku *sudoku, int row, int col, int num);

void fillBox(Sudoku *sudoku, int rowStart, int colStart);
void fillDiagonal(Sudoku *sudoku);
int fillRemaining(Sudoku *sudoku, int row, int col);
void removeKDigits(Sudoku *sudoku, int k);

void saveGame(const Sudoku *sudoku, const char *filename);
Sudoku *loadGame(const char *filename);
void playerMove(Sudoku *sudoku);

#endif

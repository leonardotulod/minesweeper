
#ifndef FUNCTIONS_H
#define FUNCTIONS_H


/* define a constant to represent a mine */
const int MINE = -1; 

/* define struct to represent a position in the game matrix */ 
struct minePosition{
  int neighborMines; 
  bool open;
};


void initializeMineMatrix (minePosition** mineMatrix, int nRows, int nCols, int nMines); 
struct minePosition** createMatrix (int m, int n);
int random(int max); 
void printMineMatrix (struct minePosition** mineMatrix, int nRows, int nCols, int nMines);



int openPosition(struct minePosition** mineMatrix, int nRows, int nCols, int row, int col); 
int countNeighborMines(struct minePosition** mineMatrix, int nRows, int nCols, int row, int col);
int countClosedPositions (struct minePosition** mineMatrix, int nRows, int nCols);

#endif
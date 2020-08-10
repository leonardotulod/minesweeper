#include <iostream> 
#include <cstdlib>
#include "functions.h"

using std::cout;
using std::endl;



int random(int max) // generate number in [0, max-1]
{
  return (rand() % max); 
} 




struct minePosition** createMatrix (int nRows, int nCols)
{
  struct minePosition** mat; 
  mat = new struct minePosition*[nRows]; 
  for (int i = 0; i < nRows; i++)
    mat[i] = new struct minePosition[nCols];
  return mat;
}


void initializeMineMatrix (struct minePosition ** mineMatrix, int nRows, int nCols, int nMines)
{

  for(int i = 0; i < nRows; ++i)
    for(int j = 0; j < nCols; j++){
      mineMatrix[i][j].neighborMines = 0;
      mineMatrix[i][j].open = false; 
    }

  int i = 0; 
  while (i < nMines){
    int row = random(nRows); // suppose that random will eventually find 
    int col = random(nCols); // a free spot for a mine. 
    if (mineMatrix[row][col].neighborMines == 0){
      mineMatrix[row][col].neighborMines = MINE;
      i = i + 1; 
    }
  }
}



void printMineMatrix (struct minePosition ** matrix, int nRows, int nCols, int nMines)
{
  int closedPositions = 0; 
  for (int i = 0; i < nCols + 2; i++) cout << "="; 
  cout << endl; 
  for (int i = 0; i < nRows; i ++){
    cout << "|"; 
    for (int j = 0; j < nCols; j++)
      if (matrix[i][j].open)
	if (matrix[i][j].neighborMines == 0) 
	  cout << " "; 
	else if (matrix[i][j].neighborMines == MINE)
	  cout << "*"; 
	else
	  cout << matrix[i][j].neighborMines; 
      else{
        closedPositions = closedPositions + 1; 
	cout << ".";
      } 
    cout << "|"<< endl; 
  }
  for (int i = 0; i < nCols + 2; i++) cout << "="; 
  cout << endl; 
  cout << closedPositions << " closed positions. " << nMines << " mines." << endl; 
}


// own function isValid
bool isValid(int nRows, int nCols, int row, int col){
	// if rows and columns are in range
	if (row >= 0 && row < nRows && col >= 0 && col < nCols){
		return true;
	} else {
		return false;
	}
}

int countClosedPositions (struct minePosition** mineMatrix, int nRows, int nCols)
{
  int numberOfClosedPositions = 0;
  
  for (int row = 0; row < nRows; row++){
	for (int col = 0; col < nCols; col++){
		if (!mineMatrix[row][col].open){
			numberOfClosedPositions++;
		}
	}
  }
  
  return numberOfClosedPositions; 
} 


int countNeighborMines(struct minePosition** mineMatrix, int nRows, int nCols, int row, int col)
{
  int numberOfNeighborMines = 0;
  
  // 1 2 3
  // 4   5
  // 6 7 8
  
  // 1
  // checking if it's a valid spot
	if (isValid(nRows, nCols, row - 1, col - 1)){
	// check if it's a mine
		if (mineMatrix[row-1][col-1].neighborMines == -1){
			numberOfNeighborMines++;
		}
	}
	
	// 2
	if (isValid(nRows, nCols, row - 1, col)){
		if (mineMatrix[row-1][col].neighborMines == -1){
			numberOfNeighborMines++;
		}
	}

	// 3
	if (isValid(nRows, nCols, row - 1, col+1)){
		if (mineMatrix[row-1][col+1].neighborMines == -1){
			numberOfNeighborMines++;
		}
	}
		
	// 4
	if (isValid(nRows, nCols, row, col-1)){
		if (mineMatrix[row][col-1].neighborMines== -1){
			numberOfNeighborMines++;
		}
	}
		
	// 5
	if (isValid(nRows, nCols, row, col+1)){
		if (mineMatrix[row][col+1].neighborMines == -1){
			numberOfNeighborMines++;
		}
	}
		
	// 6
	if (isValid(nRows, nCols, row + 1, col-1)){
		if (mineMatrix[row+1][col-1].neighborMines == -1){
			numberOfNeighborMines++;
		}
	}
		
	// 7
	if (isValid(nRows, nCols, row + 1, col)){
		if (mineMatrix[row+1][col].neighborMines == -1){
			numberOfNeighborMines++;
		}
	}
		
	// 8
	if (isValid(nRows, nCols, row + 1, col+1)){
		if (mineMatrix[row+1][col+1].neighborMines == -1){
			numberOfNeighborMines++;
		}
	}
  
  return numberOfNeighborMines;
}



int openPosition(struct minePosition** mineMatrix, int nRows, int nCols, int row, int col)
{
	
	if (!mineMatrix[row][col].open && mineMatrix[row][col].neighborMines == -1){
		cout << "BOOOOOOOOOOOOOOOOOOOOOOM" << endl;
		return -1;
	} else {
		// opens the position and counts neighbors with mines, updates cell
		mineMatrix[row][col].open = true;
		
		if (countNeighborMines(mineMatrix, nRows, nCols, row, col) > 0){
			mineMatrix[row][col].neighborMines = countNeighborMines(mineMatrix, nRows, nCols, row, col);
		}
		// if no neighbor mines, recursively opens neighboring positions
		else {
			// 1 2 3
			// 4   5
			// 6 7 8
			
			// 1
			if (isValid(nRows, nCols, row - 1, col-1) && !mineMatrix[row-1][col-1].open){
				openPosition(mineMatrix, nRows, nCols, row - 1, col - 1);
			}
			
			// 2
			if (isValid(nRows, nCols, row - 1, col) && !mineMatrix[row-1][col].open){
				openPosition(mineMatrix, nRows, nCols, row - 1, col);
			}
			
			// 3
			if (isValid(nRows, nCols, row - 1, col+1) && !mineMatrix[row-1][col+1].open){
				openPosition(mineMatrix, nRows, nCols, row - 1, col + 1);
			}
			
			// 4
			if (isValid(nRows, nCols, row, col-1) && !mineMatrix[row][col-1].open){
				openPosition(mineMatrix, nRows, nCols, row, col - 1);
			}
			
			// 5
			if (isValid(nRows, nCols, row, col+1) && !mineMatrix[row][col+1].open){
				openPosition(mineMatrix, nRows, nCols, row, col + 1);
			}
			
			// 6
			if (isValid(nRows, nCols, row + 1, col-1) && !mineMatrix[row+1][col-1].open){
				openPosition(mineMatrix, nRows, nCols, row + 1, col - 1);
			}
			
			// 7
			if (isValid(nRows, nCols, row + 1, col) && !mineMatrix[row+1][col].open){
				openPosition(mineMatrix, nRows, nCols, row + 1, col);
			}
			
			// 8
			if (isValid(nRows, nCols, row + 1, col+1) && !mineMatrix[row+1][col+1].open){
				openPosition(mineMatrix, nRows, nCols, row + 1, col + 1);
			}
			
		}
		return 0;
	}
  return 0; 
}
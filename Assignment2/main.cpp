
#include <iostream>
#include <cstdint>
#include <time.h>
#include <stdlib.h>
#include "Collection.h"
#include <math.h>

struct Maze {
	uint64_t pairOfRows[16];
	int numRows;
	int numCols;
};

void InitializeMaze(Maze& m);
void PrintMaze(const Maze& m);
void SetWalkable(Maze &m, int row, int column);
bool GetCellValue(const Maze& m, int row, int column);
Maze MakeMaze();


int main(int argc, const char * argv[])
{
	
  //seeding the random number generator
  srand((int)time(NULL));
  Maze m = MakeMaze(); //MakeMaze does not work
 

  

  //PrintMaze(m);
  
 
  return 0;
}

void InitializeMaze(Maze& m) {
	
	for (int i = 0; i < 16; i++) {
		m.pairOfRows[i] = 0;
	}

	m.numRows = 32;
	m.numCols = 32;
}

void PrintMaze(const Maze& m) {
	
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 64; j++) {

			//Number 1 is casted so that it doesn't zero out the result after the 31st shift
			//since it was being evaluated as 32bit integer on my machine
			bool bitValue = m.pairOfRows[i] & ((uint64_t) 1 << j);

			if (bitValue) {
				std::cout << "  ";
			}
			else {
				std::cout << " X";
			}

			// Change Lines after printing the 31st and 63rd bit (end of row)
			if (j == 31 || j == 63) {
				std::cout << "\n";
			}
		}
	}

}

void SetWalkable(Maze& m, int row, int column) {
	
	// Rows and Columns go from 0 to 31
	int bitArrayRow = row / 2;
	
	if (row % 2 == 0) {
		// since each index in the array represents two rows. Only looks at first set of 32 bits
		m.pairOfRows[bitArrayRow] = m.pairOfRows[bitArrayRow] | (uint64_t)1 << column;
	}
	else { //32 is added to value of column so that only the second set of 32 bits is considered
		m.pairOfRows[bitArrayRow] = m.pairOfRows[bitArrayRow] | (uint64_t)1 << column + 32;
	}
}

bool GetCellValue(const Maze& m, int row, int column) {
	bool bitValue = false;
	if (row > 31 || row < 0 || column > 31 || column < 0) {
		return false;
	}
	
	int bitArrayRow = row / 2;
	
	if ((row % 2) == 0) {
		bitValue = m.pairOfRows[bitArrayRow] & (uint64_t)1 << column;
	}
	else {
		bitValue = m.pairOfRows[bitArrayRow] & (uint64_t)1 << column + 32;
	}

	return bitValue;
}

Maze MakeMaze() {
	Maze m;
	InitializeMaze(m);
	Collection cellsToExpand;
	AddCell(cellsToExpand, 16, 16); // R16, C16 represents the center cell
	SetWalkable(m, 16, 16);
	
	int i = 0;
	while (!CollectionIsEmpty(cellsToExpand)) {

		Cell currentCell = GetRandomCell(cellsToExpand);

		int randomDirection = rand() % 5;

		if (randomDirection == 0) {
			//Go West
			if (!((currentCell.column - 2) < 0) || !GetCellValue(m, currentCell.row, currentCell.column - 2)) { //Check if neighbor (two steps way) to the left is inbounds and if it's set
				AddCell(cellsToExpand, currentCell.row, currentCell.column - 2); // Add neighbor (two steps away) to the Collection
				SetWalkable(m, currentCell.row, currentCell.column - 1); // Open Wall between the neighboring cell and the Current Cell
			}
			
		}
		else if (randomDirection == 1){
			//Go East
			if (!((currentCell.column + 2) > 31) || !GetCellValue(m, currentCell.row, currentCell.column + 2)) { //Check if neighbor (two steps way) to the right is inbounds and if it's set
				AddCell(cellsToExpand, currentCell.row, currentCell.column + 2); // Add neighbor (two steps away) to the Collection
				SetWalkable(m, currentCell.row, currentCell.column + 1); // Open Wall between the neighboring cell and the Current Cell
			}
			
		}
		else if (randomDirection == 3) {
			//Go South
			if (!((currentCell.row + 2) > 31) || !GetCellValue(m, currentCell.row + 2, currentCell.column)) { //Check if neighbor (two steps way) to the South is inbounds and if it's set
				AddCell(cellsToExpand, currentCell.row + 2, currentCell.column); // Add neighbor (two steps away) to the Collection
				SetWalkable(m, currentCell.row + 1, currentCell.column); // Open Wall between the neighboring cell and the Current Cell
			}
			
		}
		else {
			//Go North
			if (!((currentCell.row - 2) < 0) || !GetCellValue(m, currentCell.row - 2, currentCell.column)) { //Check if neighbor (two steps way) to the North is inbounds and if it's set
				AddCell(cellsToExpand, currentCell.row - 2, currentCell.column); // Add neighbor (two steps away) to the Collection
				SetWalkable(m, currentCell.row - 1, currentCell.column); // Open Wall between the neighboring cell and the Current Cell
			}
			
		}

		bool checkCurrentCellBoundaries = currentCell.row >= 0 && currentCell.row < 32 && currentCell.column >= 0 && currentCell.column < 32;
		//bool checkCurrentCellBoundaries = currentCell.column == 31 || currentCell.row == 31;
		bool checkNeighborsVertically = GetCellValue(m, currentCell.row - 2, currentCell.column) && GetCellValue(m, currentCell.row + 2, currentCell.column);
		bool checkNeighborsHorizontally = GetCellValue(m, currentCell.row, currentCell.column + 2) && GetCellValue(m, currentCell.row, currentCell.column - 2);
			
		if (checkCurrentCellBoundaries || (checkNeighborsVertically && checkNeighborsHorizontally)) {
				RemoveCell(cellsToExpand, currentCell.row, currentCell.column);
		}
		
	}
	
	return m;

}
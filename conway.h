
/***********************************************
 * An Implementation of Conway's Game of Life. *
 * ********************************************/

/*
 * David Mayes
 * 150012384
 *
 * Gavin Henderson
 *
 * AC21009
 */

#ifndef _CONWAY_
#define _CONWAY_

#include <stdio.h>
#include <stlib.h>

#include "cell.h"

//grid of cells
typedef struct MyCellGrid{
	CellGroup* head;
	int width;
	int height;
}CellGrid;

//creates a grid of cells, takes in parameters for width and height
CellGrid* createCellGrid(int newValues[][], int width, int height);

//frees the memory used by the grid
int deleteCellGrid(CellGrid* cell_grid);

//creates the next generation in Conway's Game of Life
CellGrid* nextConway(CellGrid* cell_grid);

#endif //_CONWAY_

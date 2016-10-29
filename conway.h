
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
#include <stdlib.h>

#include "cell.h"

//grid of cells
typedef struct MyCellGrid{
	CellGroup* head;
	int width;
	int height;
}CellGrid;

//creates a grid of cells, takes in parameters for width and height
CellGrid* createCellGrid(int grid_height, int grid_width, int newValues[grid_height][grid_width]);

//frees the memory used by the grid
int deleteCellGrid(CellGrid* cell_grid);

//inserts the next CellGroup
void insertCellGroup(CellGrid* cell_grid, CellGroup* cell_group);

//creates the next generation in Conway's Game of Life
CellGrid* nextConway(CellGrid* cell_grid);

#endif //_CONWAY_

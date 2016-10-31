
/**************************************************
 * An Implementation of Conway's Game of Life.    *
 *************************************************/

/*
 * David Mayes
 * 150012384
 *
 * Gavin Henderson
 * 150010848
 *
 * AC21009
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "conway.h"
#include "cell.h"

/*
 * Creates a grid of cells,
 *
 * (uses rows of CellGroups)
 * Creates 'height' number of cellGroups, with 'width' number of cells in them
 * The groups are linked together.
 */
CellGrid* createCellGrid(int grid_height, int grid_width, int newValues[grid_height][grid_width])
{

	//allocate the new CellGrid in memory
	CellGrid* newCellGrid;
	newCellGrid = calloc(1, sizeof(CellGrid));
	
	//set the sizes
	newCellGrid->width = grid_width;
	newCellGrid->height = 0; //still zero while no groups are added

	//add the cellGroups to the grid. Loops until the new grid is filled
	for( int i = 0; i < grid_height; i++){
		//create an array with the values to put into the current grid row
		int cell_group_values[grid_width];

		//zero all the values
		for(int j = 0; j < grid_width; j++){
			cell_group_values[j] = 0;
		}

		for(int j = 0; j < grid_width; j++){
			cell_group_values[j] = newValues[newCellGrid->height][j];
		}

		//create a cellGroup
		CellGroup* newCellGroup = createCellGroup(cell_group_values, grid_width);

		//insert it into the grid
		insertCellGroup(newCellGrid, newCellGroup);
	

	}
	return newCellGrid;
}

/*
 * Frees the memory used by the grid.
 * 
 * Uses deleteCellGroup()
 */
int deleteCellGrid(CellGrid* cell_grid)
{
	//check that the pointers aren't NULL
	assert(cell_grid != NULL);
	
	//if there is nothing in the grid delete it
	if(cell_grid->height == 0 ){
	
		memset(cell_grid, 0, sizeof(CellGrid));
		free(cell_grid);

		if(cell_grid != NULL){
			return 0;
		} else {
			return 1;
		}

	//otherwise loop through all the cellgroups and delete them
	} else {
		CellGroup* next = cell_grid->head;
		CellGroup* current = cell_grid->head;

		while(cell_grid->height != 0){
		
		current = next;
		//move to the next group
		if(cell_grid->height > 1){
			next = next->next;
		}
		deleteCellGroup(current);
		
		(cell_grid->height)--;

		}

		//deletes the cell grid
		memset(cell_grid, 0, sizeof(CellGrid));
		free(cell_grid);

		if(cell_grid != NULL){
			return 0;
		} else {
			return 1;
		}
	}
		
}

/*
 * Inserts the next CellGroup
 *
 * Connects all of the cells together vertically
 */
void insertCellGroup(CellGrid* cell_grid, CellGroup* cell_group)
{
	//check that the pointers aren't NULL
	assert(cell_grid != NULL);
	assert(cell_group != NULL);

	//if the cell grid is empty
	if( cell_grid->height == 0 ){
		//make cell_group the head
		cell_grid->head = cell_group;
	} else {
		//start at the head
		CellGroup* tmpGroup = cell_grid->head;

		//loop until the end of the group
		for( int i = 0; i < (cell_grid->height - 1); i++){
		       //move to the next group
		       tmpGroup = tmpGroup->next;
		}
 		//insert the new group
		tmpGroup->next = cell_group;
		cell_group->prev = tmpGroup;
	}

	//make the list loop round
	cell_group->next = cell_grid->head;
	(cell_grid->head)->prev = cell_group;	
	
	//increase the height
	(cell_grid->height)++;

	/* Connect the cells vertically */
	
	//start at the head
	Cell* cell_below = cell_group->head;
	Cell* cell_above = (cell_group->prev)->head;
	
	//connect it to the head group so it loops round
	Cell* cell_head = (cell_grid->head)->head;

	//loop through the cells
	for(int i = 0; i < (cell_grid->width); i++){
			
	//point the cells to each other
	cell_below->up = cell_above;
	cell_above->down = cell_below;

	//point this group to the head
	cell_head->up = cell_below;
	cell_below->down = cell_head;

	//move all the cells along
	cell_below = cell_below->right;
	cell_above = cell_above->right;
	cell_head = cell_head->right;

	}
		
}


/*
 * Creates the next generation in Conway's Game of Life
 *
 * Generates information from the current generation,
 * deletes it, then creates a new generation using 
 * createCellGrid().
 */
CellGrid* nextConway(CellGrid* cell_grid)
{
	//check that the pointer is not NULL
	assert(cell_grid != NULL);

	//create template for the next generation
	int values[cell_grid->height][cell_grid->width];

	//zero all the values
	for(int i = 0; i < (cell_grid->height); i++){
		for(int j = 0; j < (cell_grid->width); j++){
			//zero current
			values[i][j] = 0;
		}
	}

	//temporary cell used to loop
	Cell* tmpCell = (cell_grid->head)->head;

	//loop through the cells vertically
	for(int i = 0; i < (cell_grid->height); i++){

		//loop through the cells horizontally
		for(int j = 0; j < (cell_grid->width); j++){
			
			/* Calculate the number of living cells around the current cell	*/
			
			int live_cells = 0;
			
			//cell above
			if( (tmpCell->up)->data == 1 ){
				
				live_cells++;
			}
			//cell below
			if( (tmpCell->down)->data == 1 ){

				live_cells++;
			}
			//cell right
			if( (tmpCell->right)->data == 1 ){

				live_cells++;
			}
			//cell left
			if( (tmpCell->left)->data == 1 ){

				live_cells++;
			}
			//cell up-left
			if( ((tmpCell->up)->left)->data == 1 ){

				live_cells++;
			}
			//cell up-right
			if( ((tmpCell->up)->right)->data == 1 ){

				live_cells++;
			}
			//cell down-right
			if( ((tmpCell->down)->right)->data == 1 ){

				live_cells++;
			}
			//cell down-left
			if( ((tmpCell->down)->left)->data == 1 ){

				live_cells++;
			}
			
			/* Set the next generation's version of this cell */	
			
			//if the current cell is alive
			if( tmpCell->data == 1 ){

				//if it has two/three neighbours
				if( ( live_cells == 2 ) || ( live_cells == 3 ) ){
					//the next gen cell is alive
					values[i][j] = 1;

				} else {
					//the next gen cell is dead
					values[i][j] = 0;
				}
			
			//if the current cell is dead
			} else {

				//if it has exactly three neighbours
				if( live_cells == 3 ){
					//the next gen cell is alive
					values[i][j] = 1;

				} else {
					//the next gen cell is dead
					values[i][j] = 0;
				}

			}

		 	//move to the next cell
			tmpCell = tmpCell->right;
		}
		
		//move to the next row
		tmpCell = tmpCell->down; //move down to the next row
	}

	//save the sizes before the old cellGrid is deleted
	int grid_height = cell_grid->height;
	int grid_width = cell_grid->width;

	
	//delete the cellgrid
	deleteCellGrid(cell_grid);

	//return the new CellGrid
	return createCellGrid(grid_height, grid_width, values);
}

/*
Prints the current generation of the conway
*/
void printGrid(CellGrid* myConway)
{
	//Set up cell variables
	Cell* currentHead = myConway->head->head;
	Cell* currentCell = currentHead;
	
	//Loop downwards
	for(int i=0; i<myConway->height; i++)
	{
		//Loop sideways
		for(int j=0; j<myConway->width; j++)
		{
			//Print values
			if(currentCell->data == 0)
			{
				printf(".");
			} 
			else 
			{
				printf("1");
			}
			//Iterate sideways
			currentCell = currentCell->right;
		}
		printf("\n");
		
		//Iterate downwards
		currentCell = currentHead->down;
		currentHead = currentHead->down;
	}
}

/*
Gets initial conway from the user
*/
CellGrid* getInitialGrid()
{
	//Loops to get a valid length of row
	bool valid=false;
	int length;
	while(!valid)
	{
		printf("Please enter the length of the rows\n");
		scanf("%d",&length);
		if(length>3)
		{
			valid=true;
		}
		else
		{
			printf("You didnt enter a valid size\n");
		}
	}
	
	//Loops to get a valid height of grid
	valid=false;
	int height;
	while(!valid)
	{
		printf("Please enter the number of rows\n");
		scanf("%d",&height);
		if(height>3)
		{
			valid=true;
		}
		else
		{
			printf("You didnt enter a valid size\n");
		}
	}
	
	//Creates array of initial values
	int initialValues[height][length];
	
	//Loop for height
	for(int i=0; i<height; i++)
	{
		//Loop for width
		for(int j=0; j<length; j++)
		{
			bool valid=false;
			while(!valid)
			{
				int currentValue = 0;
				printf("(%d,%d): ",(j+1),(i+1));
				scanf("%d",&currentValue);				
				if(currentValue==1||currentValue==0)
				{
					initialValues[i][j]=currentValue;
					valid=true;
				}
				else
				{
					printf("You did not enter a valid input\n");
				}
			}
		}
	}
	
	//Returns the grid
	return createCellGrid(height, length, initialValues);
}

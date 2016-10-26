#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "cell.h"

/*
Creates a cell group and sets the size to the parameter 'num'
It then passes out a pointer to the new group after it is done 
initialising it
*/
CellGroup* createCellGroup(int num)
{
	CellGroup* newGroup;
	newGroup = malloc(sizeof(CellGroup));
	memset(newGroup, 0, sizeof(CellGroup));
	newGroup->size = 0;

	//add the cells to the group
	for(int i=0; i<num; i++)
	{
		//create a cell
		Cell* newCell = createCell(0);
		//add it
		insertCell(newGroup, newCell);
	}
	return newGroup;
}

/*
Creates a cell and sets the data of the cell to the paramater
'null' the passes out a pointer to the new cell after initialising
the variables
*/
Cell* createCell(int num)
{
	Cell* newCell = malloc(sizeof(Cell));
	memset(newCell,0,sizeof(Cell));
	newCell->data = num;
	newCell->left = NULL;
	newCell->right = NULL;
	return newCell;
}

/*
Inserts a cell into the specified group. 
*/
void insertCell(CellGroup* clgp, Cell* cl){
	//check that the pointers aren't NULL
	assert(clgp != NULL);
	assert(cl != NULL);

	//if the cellgroup is empty
	if( clgp->size == 0 ){
		//make cl the head
		clgp->head = cl;

	} else {
		//start at the head
		Cell* tmpCell = clgp->head;
		
		//loop until the end of the group
		for(int i = 1; i < (clgp->size); i++){
			tmpCell = tmpCell->right;
		}
		//insert the new cell
		tmpCell->right = cl;
		cl->left = tmpCell;
	}	

	//make the list loop round
	cl->right = clgp->head;
	clgp->head->left = cl;

	//increase the size
	clgp->size++;
}

/*
A pointer to a cell in passed in and then that memory address is then free'd
after the memory has been set to 0s. It will return 0 if memory is correctly
deleted and returns 1 otherwise
*/
int deleteCell(Cell* cl)
{
	memset(cl, 0, sizeof(Cell));
	free(cl);
	if(cl!=NULL)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/*
A pointer to a group is passed in and then that memory address is then free'd if
the group is empty of cells if it not it will loop through the cell group and free
the cells then free the group. It will return 0 if the memory is corretly deleted
and return 1 otherwise
*/
int deleteCellGroup(CellGroup* clgp)
{
	if(clgp->size==0)
	{
		memset(clgp, 0, sizeof(CellGroup));
		free(clgp);
		if(clgp!=NULL)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		Cell* current = clgp->head;
		Cell* next = current->right;
		bool cont = true;
		while(cont)
		{
			deleteCell(current);
			clgp->size--;
			current = next;
			next=current->right;
			if(current==NULL)
			{
				cont=false;
			}
		}
		memset(clgp, 0, sizeof(CellGroup));
		free(clgp);
		if(clgp!=NULL)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}	
	return 0;
}

/*
Takes in an integer number that it assumes it is between 0 and 255 (inclusive)
It then passes out a the binary number
*/
int* binaryConversion(int x)
{
	//Creates an array that will store the binary number backwards
    int backwardBinaryNumber[8];
    
    //Sets all the values to 0
    for(int k=0; k<8; k++){
    	backwardBinaryNumber[k] = 0;
    }
	
	//Creates the binary number using modulus
	int i=0;
    while(x!=0){
    	backwardBinaryNumber[i++]= x % 2;
    	x = x / 2;
    }

	//Creates the binary number in memory
	int *binaryNumber = malloc(sizeof(int)*8);
	
	//Reverses it and saves it to the new malloced memory
	for(int j=7; j>-1; j--)
	{
		binaryNumber[7-j] = backwardBinaryNumber[j];
	}
	
	//Return the int pointer
	return binaryNumber;
}

//dummy main
int main()
{
	int* binary = binaryConversion(8);
	for(int i=0;i<8;i++)
	{
		printf("%d\n",binary[i]);
	}
	
	free(binary);	
}

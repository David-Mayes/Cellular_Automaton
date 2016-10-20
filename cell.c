#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cell.h"

/*

*/
CellGroup* createCellGroup(int num)
{
	CellGroup* newGroup;
	newGroup = malloc(sizeof(CellGroup));
	memset(newGroup, 0, sizeof(CellGroup));
	newGroup->head = NULL;
	newGroup->size = num;
	return newGroup;
}

Cell* createCell(int num)
{
	Cell* newCell = malloc(sizeof(Cell));
	memset(newCell,0,sizeof(Cell));
	newCell->data = num;
	newCell->left = NULL;
	newCell->right = NULL;
	return newCell;
}

int deleteCell(Cell* cl)
{
	memset(cl, 0, sizeof(Cell));
	free(cl);
	return 0;
}

int deleteCellGroup(CellGroup* clgp)
{
	if(clgp->size==0)
	{
		memset(clgp, 0, sizeof(CellGroup));
		free(clgp);
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
	}	
	return 0;
}

//dummy main
int main()
{
}

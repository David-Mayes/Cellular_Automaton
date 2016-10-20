#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*

*/
CellGroup* createCellGroup(int num)
{
	CellGroup* newCellGroup = malloc(sizeof(CellGroup));
	memset(newCellGroup,0,sizeof(CellGroup));
	newCellGroup->head = NULL;
	newCellGroup->size = num;
	return newCellGroup;
}

Cell* createCell(int num)
{
	Cell* newCell = malloc(sizeof(Cell));
	memset(newCellGroup,0,sizeof(Cell));
	newCell->data = num;
	newCell->left = NULL;
	newCell->right = NULL;
	return newCell;
}

int deleteCell(Cell* cl)
{
	memset(cl, 0, sizeof(Cell));
	free(cl);
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
			deleteCell(current)
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
}

int main()
{
}
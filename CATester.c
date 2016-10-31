#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cell.h"
#include "conway.h"


int main()
{
	bool running = true;
	while(running)
	{
		printf("\n1) Save to file (60 Lines)\n");
		printf("2) Print to screen (30 Lines)\n");
		printf("3) Run conways game of life (30 screens)\n");
		printf("0) Quit\n");
		int choice=0;
		printf("Enter your choice: ");
		scanf("%d", &choice);
		
		if(choice==0)
		{
			running=false;
		}
		else if(choice==1)
		{
			int* ruleset = binaryConversion(getUserInput());
			CellGroup* newCellGroup = getInitialGroup();
			saveOutput(newCellGroup, ruleset, 60);
			deleteCellGroup(newCellGroup);
			free(ruleset);
		}
		else if(choice==2)
		{
			int* ruleset = binaryConversion(getUserInput());
			CellGroup* newCellGroup = getInitialGroup();
			for(int i=0; i<30; i++)
			{
				printCellGroup(newCellGroup);
				newCellGroup = nextGen(newCellGroup, ruleset);
				delay(1);
			}
			deleteCellGroup(newCellGroup);
			free(ruleset);
		}
		else if(choice==3)
		{
			CellGrid* myGrid = getInitialGrid();
			printGrid(myGrid);

			for(int i=0; i<30; i++)
			{
				myGrid = nextConway(myGrid);
				printGrid(myGrid);

				delay(1);
			}
			deleteCellGrid(myGrid);
		}
		else
		{
			printf("INVALID INPUT\n");
		}
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cell.h"
//#include "conway.h"

int main()
{
	bool running = true;
	while(running)
	{
		printf("\n1) Save to file\n");
		printf("2) Print to screen\n");
		printf("3) Run conways game of life\n");
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
			saveOutput(newCellGroup, ruleset, 30);
			deleteCellGroup(newCellGroup);
		}
		else if(choice==2)
		{
			int* ruleset = binaryConversion(getUserInput());
			CellGroup* newCellGroup = getInitialGroup();
			for(int i=0; i<60; i++)
			{
				printCellGroup(newCellGroup);
				newCellGroup = nextGen(newCellGroup, ruleset);
				delay(1);
			}
			deleteCellGroup(newCellGroup);
		}
		else if(choice==3)
		{
			//RUN CONWAY STUFF
		}
		else
		{
			printf("INVALID INPUT\n");
		}
	}
	
	return 0;
}
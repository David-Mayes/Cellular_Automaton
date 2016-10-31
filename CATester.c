/*
Gavin Henderson and David Mayes
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cell.h"
#include "conway.h"

//Runs when the program is executed
int main()
{
	//Loops until the user doesnt want to run the program anymore
	bool running = true;
	while(running)
	{
		
		//Displays the options to the user
		printf("\n1) Save to file (60 Lines)\n");
		printf("2) Print to screen (30 Lines)\n");
		printf("3) Run conways game of life (30 screens)\n");
		printf("0) Quit\n");
		
		//Takes in the users choice
		int choice=0;
		printf("Enter your choice: ");
		scanf("%d", &choice);
		
		//Runs if the user wants to quit the program
		if(choice==0)
		{
			running=false;
		}
		
		//Runs if the user wants to save to a file 
		else if(choice==1)
		{
			//Gets ruleset and calls the function that will save the
			//output to a file. Then delete the CellGroup and ruleset
			int* ruleset = binaryConversion(getUserInput());
			CellGroup* newCellGroup = getInitialGroup();
			saveOutput(newCellGroup, ruleset, 60);
			deleteCellGroup(newCellGroup);
			free(ruleset);
		}
		//Runs if the user wants to print to the screen
		else if(choice==2)
		{
			//Gets the ruleset and then loops 30 times calling the print
			//function. Then deletes the Cell Group and ruleset.
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
		//Runs if the user wants to use the conways game of life
		else if(choice==3)
		{
			//Gets the initial grid then loops 30 times and prints out
			//every screen to the user and then deletes the cell grid.
			CellGrid* myGrid = getInitialGrid();
			for(int i=0; i<30; i++)
			{
				printGrid(myGrid);
				printf("\n");
				myGrid = nextConway(myGrid);
				delay(1);
			}
			deleteCellGrid(myGrid);
		}
		//Runs if the user does not enter an expected option
		else
		{
			printf("INVALID INPUT\n");
		}
	}
}

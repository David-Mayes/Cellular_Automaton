#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cell.c"
#include "conway.h"

int main()
{
	bool running = true;
	while(running)
	{
		printf("\nWould you like to save a CA to a file?\n");
		printf("");
	}
	
	
	
	
	
	
	
	int* ruleset = binaryConversion(getUserInput());
	CellGroup* newCellGroup = getInitialGroup();
	
	saveOutput(newCellGroup, ruleset, 20);
	printCellGroup(newCellGroup);
	while(true)
	{
		newCellGroup = nextGen(newCellGroup, ruleset);
		printCellGroup(newCellGroup);
		delay(1);
	}
	deleteCellGroup(newCellGroup);
}
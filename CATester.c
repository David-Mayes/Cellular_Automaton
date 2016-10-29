#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "cell.h"
#include "conway.h"

//Creates a delay when called
static void delay(unsigned int seconds)
{
	unsigned int wait = time(0)+seconds;
	while(time(0)<wait);
}

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

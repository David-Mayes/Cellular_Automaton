#include <stdio.h>
#include <stdlib.h>
#include "cell.c"
#include "conway.h"

int main()
{
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
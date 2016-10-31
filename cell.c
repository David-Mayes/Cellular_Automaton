#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

#include "cell.h"

/*
Creates a cell group and sets the size to the parameter 'num'
It then passes out a pointer to the new group after it is done 
initialising it
*/
CellGroup* createCellGroup(int newValues[], int newGroupSize)
{
	//Making the new cellgroup in memory and initialising it
	CellGroup* newGroup;
	newGroup = calloc(1, sizeof(CellGroup));
	newGroup->size = 0;

	//add the cells to the group
	for(int i=0; i<newGroupSize; i++)
	{
		//create a cell
		Cell* newCell = createCell(newValues[i]);
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
	Cell* newCell = calloc(1, sizeof(Cell));
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
	//Sets the memory location to '0's and gives it back to the memory
	memset(cl, 0, sizeof(Cell));
	free(cl);
	
	//Makes sure that the cell is successfully deleted
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
	//Deletes the cell group if there is nothing in the cellgroup
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
	//Otherwise it loops through all the elements in the cell group and
	//will delete each cell
	else
	{
		Cell* next = clgp->head;
		Cell* current = clgp->head;

		for(int i = 0; i < (clgp->size); i++)
		{
			next = current->right;
			deleteCell(current);
			
			if(next != NULL)
			{
				current = next;
			}

		}

		//Finally deletes the cell group
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

/*
Takes in a cell group and a ruleset then passes out the cellgroup
that is generated based on the previous cell group and the ruleset
*/
CellGroup* nextGen(CellGroup* clgp, int* ruleset)
{
	//Loops for the size of the cellgroup and sets 'values' to 0
	int values[clgp->size];
	for(int i=0; i<clgp->size; i++)
	{
		values[i] = 0;
	}
	
	//Loops through all the elements in clgp and applying the rules based on
	//the ruleset passed in
	Cell* current = clgp->head;
	for(int i=0;i<clgp->size;i++)
	{
		if(current->left->data==1 && current->data==1 && current->right->data==1)
		{
			values[i] = ruleset[0];
		}
		else if(current->left->data==1 && current->data==1 && current->right->data==0)
		{
			values[i] = ruleset[1];
		}
		else if(current->left->data==1 && current->data==0 && current->right->data==1)
		{
			values[i] = ruleset[2];
		}
		else if(current->left->data==1 && current->data==0 && current->right->data==0)
		{
			values[i] = ruleset[3];
		}
		else if(current->left->data==0 && current->data==1 && current->right->data==1)
		{
			values[i] = ruleset[4];
		}
		else if(current->left->data==0 && current->data==1 && current->right->data==0)
		{
			values[i] = ruleset[5];
		}
		else if(current->left->data==0 && current->data==0 && current->right->data==1)
		{
			values[i] = ruleset[6];
		}
		else if(current->left->data==0 && current->data==0 && current->right->data==0)
		{
			values[i] = ruleset[7];
		}
		//move to the next node
		current = current->right;
	}

	//Saving the size before we delete it so we can pass it into the next generation
	int clgpSize = clgp->size;
	
	//Deletes the cell and makes sure it is done correctly
	int test = deleteCellGroup(clgp);
	assert( test == 0 );
	
	//returns the new cellgroup
	return createCellGroup(values, clgpSize);
}

//Gets the decimal number for the ruleset from the user and validates it
int getUserInput()
{
	//Sets up a validation that will run until a valid input is given
	bool valid = false;
	int input;
	while(!valid)
	{
		printf("Please enter a number to be used as the ruleset between 0 and 255\n");
		scanf("%d", &input);
		if(input>=0 && input<=255)
		{
			valid = true;
		}
		else
		{
			printf("INVALID NUMBER\n");
		}
	}
	
	//Returns the validated input to the user
	return input;
}

//gets the data in the starting cell group and then returns the cellgroup
CellGroup* getInitialGroup()
{
	//Loops to get a valid length of row
	bool valid=false;
	int input;
	while(!valid)
	{
		printf("Please enter the length of the first row\n");
		scanf("%d",&input);
		if(input>3)
		{
			valid=true;
		}
		else
		{
			printf("You didnt enter a valid size\n");
		}
	}
	
	//Loops for the length of the row and gets values from the user and then 
	//saves them into the values array
	printf("Enter the data in the first row (0 or 1)\n");
	int initialValues[input];
	for(int i=0;i<input;i++)
	{
		bool valid=false;
		while(!valid)
		{
			int currentValue = 0;
			printf("%d: ",(i+1));
			scanf("%d",&currentValue);
			if(currentValue==1||currentValue==0)
			{
				initialValues[i]=currentValue;
				valid=true;
			}
			else
			{
				printf("You did not enter a valid input\n");
			}
		}
	}
	
	//Then creates a cellgroup based on the values passed in
	return createCellGroup(initialValues, input);
}

/*
 * Prints a cell group
 */
void printCellGroup(CellGroup* clgp)
{
	//cell to be printed
	Cell* current = clgp->head;

	//loop through
	for(int i = 0; i<(clgp->size); i++){
		//print the correct state
		if(current->data == 0){
			printf(".");
		} else {
			printf("1");
		}
		//move to the next node
		current = current->right;
	}
	//new line for next generation
	printf("\n");
}

//Creates a delay when called
void delay(unsigned int seconds)
{
	unsigned int wait = time(0)+seconds;
	while(time(0)<wait);
}

//Saves a set number of line to a file
void saveOutput(CellGroup* clgp, int* ruleset, int lines)
{
	//Opens the file and saves it to 'output'
	FILE* output = fopen("CAoutput.txt","w");
	
	//Loops for the number of lines you want to save
	for(int i=0; i<lines ;i++)
	{
	
		//Loops through the cells in the group and
		//save things individually
		Cell* current = clgp->head;
		for(int j=0; j<(clgp->size); j++)
		{
			if(current->data==0)
			{
				fprintf(output,".");
			}
			else
			{
				fprintf(output,"0");
			}
			current = current->right;
		}
		fprintf(output,"\n");
		
		//Gets the next cellgroup
		clgp = nextGen(clgp, ruleset);
	}
	
	//closes the text document
	fclose(output);
}

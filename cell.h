/**
 * David Mayes
 * 150012384
 *
 *
 * AC21009
 * */

#ifndef _CELL_
#define _CELL_

#include <stdio.h>
#include <stdbool.h>

//the cell, points to the cell before and the cell after
typedef struct MyCell{
	int data;
	struct MyCell* left;
	struct MyCell* right;
}Cell;

//the cellular automaton has a pointer to the head and the size
typedef struct MyCellGroup{
	Cell* head;
	int size;
}CellGroup;


//creates a CellGroup takes a int for the size and returns a pointer
CellGroup* createCellGroup(int newValues[]);

//takes a pointer to a cellgroup and frees its memory
int deleteCellGroup(CellGroup* clgp);

//takes an int, stores it in a Cell and returns a pointer to it
Cell* createCell(int num);

//inserts a cell into the specified group
void insertCell(CellGroup* clgp, Cell* cl);

//takes a pointer to a Cell and free it's memory
int deleteCell(Cell* cl);

//Creates the next generation of the automaton
CellGroup* nextGen(CellGroup* clgp, int* ruleset);

//converts a decimal value to a binary one and returns it
int* binaryConversion(int x);

//Gets the decimal number for the ruleset from the user and validates it
int getUserInput();

//Gets the starting cell group from the user and puts it in a cell group
CellGroup* getIntialGroup();

//prints a cell group
void printCellGroup(CellGroup* clgp);

#endif //_CELL_

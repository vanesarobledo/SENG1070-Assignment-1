/*
* FILE : main.c
* PROJECT : SENG1070 Assignment 1
* PROGRAMMER : Vanesa Robledo
* FIRST VERSION : 2025-01-29
* DESCRIPTION :
* This program allows for file processing operations - filtering, transforming, summarizing
* and saving the changes.
* This is the main file containing the menu system to allow the user to load a file, transform
* the file, and save the data to an output file, implemented using function pointers.
*/

#include <stdio.h>
#pragma warning(disable:4996) // Disable warnings in Visual Studio

#include "operations.h"
#include "fileProcessing.h"

// FUNCTION PROTOTYPES
void loadMenu();

int main(void)
{
	// INTIALIZE DATA
	FILE* file = NULL;

	file = loadFile();

	// Close file
	fclose(file);

	return 0;
}

//
// FUNCTION : loadMenu
// DESCRIPTION :
//		 This function prints the user menu to the console.
// PARAMETERS :
//		 none
// RETURNS :
//		 void
//
void loadMenu() {
	printf("");
}
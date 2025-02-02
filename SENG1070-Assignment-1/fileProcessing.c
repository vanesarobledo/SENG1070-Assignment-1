/*
* FILE : main.c
* PROJECT : SENG1070 Assignment 1
* PROGRAMMER : Vanesa Robledo
* FIRST VERSION : 2025-01-29
* DESCRIPTION :
* 
* This file contains functions to process the input and output files.
*/

#include "fileProcessing.h"
#pragma warning(disable:4996) // Disable warnings in Visual Studio

// FUNCTIONS

// FUNCTION : loadFile
// DESCRIPTION :
//			This function asks a user for the name of a file and loads it (or creates it if it doesn't exist)
//			and returns the file pointer
// PARAMETERS :
//			none
// RETURNS :
//			int*	:	Pointer to a file		
//
FILE* loadFile(void) {
	FILE* file = NULL; // File pointer
	char filename[FILENAME_SIZE] = ""; // Name of file
	char ext[] = ".txt"; // File extension
	char buffer[INPUT_SIZE] = ""; // Buffer for user input

	// Flag for valid input
	bool validFileName = false;

	while (!validFileName)
	{
		// Prompt user for file name
		printf("Enter name of file (before .txt): ");
		fgets(buffer, INPUT_SIZE, stdin);

		// Validate input
		if (sscanf(buffer, "%s", &filename) == 0) {
			printf("Invalid input. Please try again.\n");
		}
		else {
			// Concatenate file extension and file name
			strcat(filename, ext);
			validFileName = true;
		}
	}

	// Open file for reading
	file = fopen(filename, "a+");
	if (file == NULL) {
		// Exit if there is a failure to open file
		printf("Error opening file. Exiting program...\n");
		return EXIT_FAILURE;
	}
	else {
		// Successfully load the file
		printf("%s loaded.\n", filename);
		return file;
	}
}

//
// FUNCTION : saveFile
// DESCRIPTION :
//			
// PARAMETERS :
//		int* file	:	Pointer to file
// RETURNS :
//			
//
void saveFile(int* file) {

}
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

// Define constants
#define	USER_CHOICE_LENGTH	4

// FUNCTION PROTOTYPES
void loadMenu(void);
char menuChoice(void);

int main(void)
{
	// INTIALIZE DATA
	FILE* fpFile = NULL; // File pointer

	char choice = NULL; // User choice for menu

	bool running = true; // Flag to loop menu

	while (running) {
		loadMenu();
		choice = menuChoice();

		switch (choice)
		{
		// [1] Load file
		case '1':
			fpFile = loadFile();
			break;

		// [2] View lines
		case '2':
			printf("Call viewLines() here.\n");
			break;

		// [3] Filter lines
		case '3':
			printf("Call filterLines() here.\n");
			break;

		// [4] Transform lines
		case '4':
			printf("Call transformLines() here.\n");
			break;

		// [5] Summarize lines
		case '5':
			printf("Call summarizeLines() here.\n");
			break;

		// [6] Save changes to file
		case '6':
			printf("Call saveFile() here.\n");
			break;

		// [0] Exit the program
		case '0':
			printf("Exiting program...");
			// Close file if it is open
			if (fpFile != NULL) {
				if (fclose(fpFile) != 0) {
					printf("Error closing file. Exiting program...\n");
					return EXIT_FAILURE;
				}
			}
			// Break loop
			running = false;
			break;
		// Any other input: invalid choice
		default:
			printf("Invalid choice. Please try again.\n\n");
			break;
		}

	}

	return EXIT_SUCCESS;
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
void loadMenu(void) {
	printf("File Processing Operations Menu:\n");
	printf("[1] Load file\n");
	printf("[2] View lines\n");
	printf("[3] Filter lines\n");
	printf("[4] Transform lines\n");
	printf("[5] Summarize lines\n");
	printf("[6] Save changes to file \n");
	printf("[0] Exit program\n");
}

// menuChoice() borrows some code from: 
/*
* TITLE : getCharacter function in Focused Assignment 6
* AUTHOR : V. Robledo
* DATE : 2024-11-22
* VERSION : 1.0
* AVAILABIILTY : https://github.com/Conestoga-SENG1005F24/focused-6-vanesarobledo/blob/main/Focused-6/Student.cpp
*/
//
// FUNCTION : menuChoice
// DESCRIPTION :
//		 This function prompts the user to input a menu operation and returns a character
// PARAMETERS :
//		 none
// RETURNS :
//		 char	: User choice
//
char menuChoice(void) {
	char buffer[INPUT_SIZE] = ""; // Buffer to store user input
	char charInput = NULL; // Variable to store character
	bool valid = false; // Flag to loop user input

	while (!valid) {
		printf("Enter choice: ");
		fgets(buffer, INPUT_SIZE, stdin); // Get user input with fgets()
		buffer[strlen(buffer) - 1] = '\0'; // Remove trailing newline character input
		if (sscanf(buffer, "%c", &charInput) == 0) { // Validate user input with sscanf() 
			printf("Invalid input. Please try again.\n");
		}
		else
		{
			valid = true;
		}
	}

	return charInput; // Return user character choice
}


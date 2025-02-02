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

// FUNCTION PROTOTYPES
void loadMenu(void);
void help(void);
char menuChoice(void);

// DISPATCH TABLE
// Transformation Functions
enum Transformations {
	FILTER,		// Index 0: Points to filtering lines function
	TRANSFORM,	// Index 1: Points to transforming lines function
	SUMMARIZE	// Index 2: Points to summarizing function
};
typedef int processingFunction(Line** head);
processingFunction *dispatchProcessing[] = {
	filterLines,	
	transformLines,	
	summarizeLines,	
};


int main(void)
{
	// INITIALIZE DATA

	FILE* fpFile = NULL; // File pointer

	// Menu operations
	char choice = NULL; // User choice for menu
	bool running = true; // Flag to loop menu
	int savedFile; // Store return code for saveFile() function


	// Initialize a linked list of file lines
	Line* head = NULL;

	while (running) {
		loadMenu();
		choice = menuChoice();

		switch (choice)
		{
		// [1] Load file
		case '1':
			fpFile = loadFile("a+");
			head = storeFileData(fpFile);
			break;

		// [2] View lines
		case '2':
			if (head != NULL) {
				viewLines(head);
			}
			else {
				printf("No data loaded.\n");
			}
			break;

		// [3] Filter lines
		case '3':
			dispatchProcessing[FILTER](&head);
			printf("Filtered lines: \n");
			viewLines(head);
			break;

		// [4] Transform lines
		case '4':
			dispatchProcessing[TRANSFORM](&head);
			printf("Transformed Lines:\n");
			viewLines(head);
			break;

		// [5] Summarize lines
		case '5':
			dispatchProcessing[SUMMARIZE](&head);
			break;

		// [6] Save changes to file
		case '6':
			fpFile = loadFile("w");
			savedFile = saveFile(fpFile, &head);
			if (savedFile == VALID) {
				printf("Changes saved to file successfully.\n\n");
			}
			else
			{
				printf("Changes not saved to file.\n\n");
			}
			break;

		// [H] Help
		case 'h':
		case 'H':
			help();
			break;

		// [0] Exit the program
		case '0':
			// Free dynamically-allocated memory
			if (head != NULL) {
				freeList(&head);
			}
			// Set loop to false
			running = false;
			printf("Exiting program...\n");
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
//		 void	:	This function does not take any parameters.
// RETURNS :
//		void	:	This function does not return a value.
//
void loadMenu(void) {
	printf("--------------------------------\n");
	printf("File Processing Operations Menu:\n");
	printf("--------------------------------\n");
	printf("[ 1 ] Load file\n");
	printf("[ 2 ] View lines\n");
	printf("[ 3 ] Filter lines\n");
	printf("[ 4 ] Transform lines\n");
	printf("[ 5 ] Summarize lines\n");
	printf("[ 6 ] Save changes to file \n");
	printf("[ H ] Help\n");
	printf("[ 0 ] Exit program\n\n");
}

//
// FUNCTION : help
// DESCRIPTION :
//		 This function prints a description of all of the functions to the console
// PARAMETERS :
//		 void	:	This function does not take any parameters.
// RETURNS :
//		void	:	This function does not return a value.
//
void help(void) {
	printf("Help Documentation:\n");
	printf("[ 1 ] Load file: This option data from a .txt file after you provide the name. If there is nothing in the file, then data will not be loaded. The maximum line size is 200 characters.\n\n");
	printf("[ 2 ] View lines: This option displays the data loaded from the .txt file.\n\n");
	printf("[ 3 ] Filter lines: This option allows you to enter two keywords to filter the lines of the file. If the keyword is present in the line, the line is deleted.\n\n");
	printf("[ 4 ] Transform lines: This option allows you to transform each line of the file depending on a transformation rule: uppercase (u/U), lowercase (l/L), or reverse. (r/R).\n");
	printf("Hey, since you actually opened the help documentation, here's a secret: there is an extra rule to transform lines. Enter '*' to change every line to 'Glory to Arstotzka.'.\n\n");
	printf("[ 5 ] Summarize lines: This option allows you to enter a keyword and displays the total number of lines in the file, the frequency of the keyword you specified, and the average length of each line.\n\n");
	printf("[ 6 ] Save changes to file: This option saves any filtered or transformed lines to a file. If you specify the name of a file that already exists, it will overwrite the data. \n\n");
	printf("[ 0 ] Exit program: This option exits the program.\n\n");
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
//		 void	:	This function does not take any parameters.
// RETURNS :
//		 char	:	User choice
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


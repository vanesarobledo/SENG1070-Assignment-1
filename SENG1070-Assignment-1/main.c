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
#include "operations.h"

// FUNCTION PROTOTYPES
void help(void);
void secret(void);
void exitProgram(Line**);

// Functin Pointer Protoypes
void performHelp(void (*callback)());
void performFile(FILE*, Line**, char[], void (*callback)(FILE*, Line**, char[]));
void performProcessing(Line**, void (*callback)(Line**));

int main(void)
{
	// Dispatch table for helper function
	typedef struct {
		const char* command;
		void (*handler)(void);
	} Helper;

	Helper commands[] = {
		{"help", help},
		{"secret", secret}
	};

	// Dispatch table for file functions
	typedef struct {
		const char* command;
		void (*handler)(FILE*, Line**, char[]);
	} FileFunction;

	FileFunction dispatchFile[] = {
		{"load", loadFile},
		{"save", saveFile}
	};

	// Dispatch table for processing functions
	typedef struct {
		const char* command;
		void (*handler)(Line**);
	} Processsing;

	Processsing dispatchProcessing[] = {
		{"view", viewLines},
		{"filter", filterLines},
		{"transform", transformLines},
		{"summarize", summarizeLines},
		{"exit", exitProgram}
	};

	// Define constants
	const int knumCommands = sizeof(commands) / sizeof(commands[0]);
	const int knumProcessingCommands = sizeof(dispatchProcessing) / sizeof(dispatchProcessing[0]);

	// INITIALIZE DATA
	FILE* fpFile = NULL; // File pointer
	Line* head = NULL; // Initialize a linked list of file lines
	bool running = true; // Flag to loop menu
	bool found = false; // Flag to find valid command

	char buffer[INPUT_SIZE] = ""; // Buffer to store input
	char menuChoice[INPUT_SIZE] = ""; // Store user menu choice
	char mode[CHAR_SIZE] = "";  // Store file mode

	printf("=======================================================\n");
	printf("FILE PROCESSING PROGRAM by Vanesa Robledo\n");
	printf("=======================================================\n");
	printf("Load a file by typing 'load'. View the data with 'view' and process the data with one of 'filter', 'transform', or 'summarize'. Exit the program with 'exit'. For more details, type 'help'.\n");

	while (running) {
		printf("> ");
		fgets(buffer, INPUT_SIZE, stdin); // Get user input
		_strlwr(buffer); // Convert to lowercase for case insensitivity
		if (sscanf(buffer, "%99s", &menuChoice) > 0) // Validate user input
		{
			found = false;

			for (int i = 0; i < knumCommands; i++)
			{
				// Helper Commands
				// If command is found, execute callback
				if (strcmp(menuChoice, commands[i].command) == 0)
				{
					performHelp(commands[i].handler);
					found = true;
				}
				// File Commands
				else if (strcmp(menuChoice, dispatchFile[i].command) == 0)
				{
					if (strcmp(menuChoice, "load") == 0) {
						strncpy(mode, "a+", CHAR_SIZE);
					}
					else if (strcmp(menuChoice, "save") == 0) {

						strncpy(mode, "w+", CHAR_SIZE);
					}
					performFile(fpFile, &head, mode, dispatchFile[0].handler);
					found = true;
				}
			}

			// Processing Commands
		//	for (int i = 0; i < knumCommands; i++)
		//	{
		//		// If command is found, execute callback
		//		if (strcmp(menuChoice, commands[i].command) == 0)
		//		{
		//			performHelp(commands[i].handler);
		//			found = true;
		//		}
		//	}

		}

		if (!found) {
			printf("Invalid menu option. Type 'help' for a list of commands.\n\n");
		}

	}
	return EXIT_SUCCESS;
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
	printf("------------------------------------------------------\n");
	printf("File Processing Commands:\n");
	printf("------------------------------------------------------\n");
	printf("load:\t\tThis option data from a .txt file after you provide the name.\n\t\tIf there is nothing in the file, then data will not be loaded. The maximum line size is 200 characters.\n\n");
	printf("save:\t\tThis option saves any filtered or transformed lines to a file.\n\t\tIIf you specify the name of a file that already exists, it will overwrite the data. \n\n");
	printf("\n");
	printf("------------------------------------------------------\n");
	printf("File Commands:\n");
	printf("------------------------------------------------------\n");
	printf("view:\t\tThis option displays the data loaded from the .txt file.\n\n");
	printf("filter:\t\tThis option allows you to enter two keywords to filter the lines of the file.\n\t\tIf one of the keywords is present in the line, the line is deleted.\n\n");
	printf("transform:\tThis option allows you to transform each line of the file depending on a transformation rule:\n\t\tuppercase (u/U), lowercase (l/L), or reverse. (r/R).\n\n");
	printf("summarize:\tThis option allows you to enter a keyword and displays the total number of lines in the file,\n\t\tthe frequency of the keyword you specified, and the average length of each line.\n\n");
	printf("exit:\t\tThis option exits the program.\n\n");
}

//
// FUNCTION : secret
// DESCRIPTION :
//		 This function prints a secret.
// PARAMETERS :
//		 void	:	This function does not take any parameters.
// RETURNS :
//		void	:	This function does not return a value.
//
void secret(void) {
	printf("secret:\t\tThere is an extra rule to transform lines.\n\t\tEnter '*' to change every line to 'Glory to Arstotzka.'.\n\n");
}

//
// FUNCTION : exitProgram
// DESCRIPTION :
//			This function exits the program
// PARAMETERS :
//		Line** head		:	Pointer to head of linked list
// RETURNS :
//		void			:	This function does not return a value
//
void exitProgram(Line** head) {
	// Free dynamically-allocated memory
	free(*head);

	printf("Exiting program...\n");
	exit(EXIT_SUCCESS);
}

// DISPATCH FUNCTIONS

//
// FUNCTION : performHelp
// DESCRIPTION :
//			This function performs the Help function.
// PARAMETERS :
//		void(*callback())	:	This function uses a callback.
// RETURNS :
//		void				:	This function does not return a value
//
void performHelp(void (*callback)()) {
	if (callback != NULL) {
		callback();
	}
	else {
		printf("Invalid command. Please try again.\n");
	}
}

//
// FUNCTION : performProcess
// DESCRIPTION :
//			This function performs file-processing related functions
// PARAMETERS :
//		void(*callback())	:	This function uses a callback.
// RETURNS :
//		void				:	This function does not return a value
//
void performProcess(void (*callback)()) {
	if (callback != NULL) {
		callback();
	}
	else {
		printf("Invalid command. Please try again.\n");
	}
}

//
// FUNCTION : performFile
// DESCRIPTION :
//			This function performs file-related functions
// PARAMETERS :
//			void(*callback(FILE*, Line**, char[])))	:	This function uses a callback.
// RETURNS :
//			void	:	This function does not return a value
//
void performFile(FILE* file, Line** head, char mode[], void (*callback)(FILE*, Line**, char[])) {
	if (callback != NULL) {
		callback(file, head, mode);
	}
	else {
		printf("Invalid command. Please try again.\n");
	}
}

//
// FUNCTION : performProcess
// DESCRIPTION :
//			This function performs file-processing related functions
// PARAMETERS :
//			void (*callback)(Line**)	:	This function uses a callback.
// RETURNS :
//		void	:	This function does not return a value
//
void performProcessing(Line** head, void (*callback)(Line**)) {
	if (callback != NULL) {
		callback(head);
	}
	else {
		printf("Invalid command. Please try again.\n");
	}
}
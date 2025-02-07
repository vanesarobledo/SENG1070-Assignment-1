/*
* FILE : main.c
* PROJECT : SENG1070 Assignment 1
* PROGRAMMER : Vanesa Robledo
* FIRST VERSION : 2025-01-29
* DESCRIPTION :
* This program allows for file processing operations - filtering, transforming, summarizing -
* and saving the changes to a file.
* This is the main file containing the menu system to allow the user to load a file, transform
* the file, and save the data to an output file, implemented using function pointers.
*/

#include <stdio.h>
#include "operations.h"

// FUNCTION PROTOTYPES
void help(void);
void test(void);
void secret(void);
void kris(void);
void exitProgram(Line**);

// Functin Pointer Protoypes
void performHelp(void (*callback)());
void performFile(FILE**, Line**, char[], void (*callback)(FILE*, Line**, char[]));
Line* performProcessing(Line**, Line* (*callback)(Line**));

int main(void)
{
	// Dispatch table for helper function
	typedef struct {
		const char* command;
		void (*handler)(void);
	} Helper;

	Helper commands[] = {
		{"help", help},
		{"test", test},
		{"secret", secret},
		{"kris", kris}
	};

	// Dispatch table for file functions
	typedef struct {
		const char* command;
		void (*handler)(FILE**, Line**, char[]);
	} FileFunction;

	FileFunction dispatchFile[] = {
		{"load", loadFile},
		{"save", saveFile}
	};

	// Dispatch table for processing functions
	typedef struct {
		const char* command;
		Line* (*handler)(Line**);
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
	const int knumFileCommands = sizeof(dispatchFile) / sizeof(dispatchFile[0]);
	const int knumProcessingCommands = sizeof(dispatchProcessing) / sizeof(dispatchProcessing[0]);

	// INITIALIZE DATA
	FILE* fpFile = NULL; // File pointer
	Line* head = NULL; // Initialize a linked list of file lines
	bool running = true; // Flag to loop menu
	bool found = false; // Flag to find valid command

	char buffer[INPUT_SIZE] = ""; // Buffer to store input
	char menuChoice[INPUT_SIZE] = ""; // Store user menu choice
	char mode[CHAR_SIZE] = "";  // Store file mode

	printf("===================================================================\n");
	printf("SENG1070 Assignment 1 - File Processing and Function Pointers in C\n");
	printf("by Vanesa Robledo\n");
	printf("===================================================================\n");
	printf("Load a file by typing 'load' and view the data with 'view'.\nProcess the data with one of 'filter', 'transform', or 'summarize'.\nSave changes to file with 'save'.\nExit the program with 'exit'.\nView testing-related commands with 'test'. For more details, enter 'help'.\n");

	while (running) {
		printf("> ");
		fgets(buffer, INPUT_SIZE, stdin); // Get user input
		_strlwr(buffer); // Convert to lowercase for case insensitivity
		if (sscanf(buffer, "%s", &menuChoice) > 0) // Validate user input
		{
			// Reset value of valid command
			found = false;

			// >>>>>>>>>>>>>>>>> Testing Commands
			// Loads input.txt automatically
			if (strcmp(menuChoice, "input") == 0 || strcmp(menuChoice, "input.txt") == 0) {
				fpFile = fopen("input.txt", "a+");
				if (fpFile == NULL) {
					// Exit if there is a failure to open file
					printf("Error opening file. Exiting program...\n");
					exit(EXIT_FAILURE);
				}
				head = storeFileData(fpFile);
				found = true;
			}

			// Saves to output.txt automatically
			if (strcmp(menuChoice, "output") == 0 || strcmp(menuChoice, "output.txt") == 0) {
				fpFile = fopen("output.txt", "w+");
				if (fpFile == NULL) {
					printf("Error opening file. Exiting program...\n");
					exit(EXIT_FAILURE);
				}
				Line* current = head;
				while (current != NULL) {
					// Ensure line isn't empty
					if (strlen(current->line) != 0) {
						// Write to file
						if (fprintf(fpFile, "%s", current->line) > 0) {
							current = current->next;
						}
					}
				}
				if (fclose(fpFile) != 0) {
					printf("Error closing file.\n");
					exit(EXIT_FAILURE);
				}
					printf("Data saved to file successfully.\n\n");
					found = true;
				}
			// >>>>>>>>>>>>>>>>> End Testing Commands

			// Helper Commands
			for (int i = 0; i < knumCommands; i++)
			{
				// If command is found, execute callback
				if (strcmp(menuChoice, commands[i].command) == 0)
				{
					performHelp(commands[i].handler);
					found = true;
				}
			}

			// File Commands
			for (int i = 0; i < knumFileCommands; i++)
			{
				if (strcmp(menuChoice, dispatchFile[i].command) == 0)
				{
					// Load file - pass "a+" as file opening mode
					if (strcmp(menuChoice, "load") == 0) {
						strncpy(mode, "a+", CHAR_SIZE);
					}
					// Save file - pass "w+" as file opening mode
					else if (strcmp(menuChoice, "save") == 0) {

						strncpy(mode, "w+", CHAR_SIZE);
					}
					// If command is found, execute callback
					performFile(fpFile, &head, mode, dispatchFile[i].handler);
					found = true;
				}
			}

			// Processing Commands
			for (int i = 0; i < knumProcessingCommands; i++)
			{
				// If command is found, execute callback
				if (strcmp(menuChoice, dispatchProcessing[i].command) == 0)
				{
					// Exit program
					if (strcmp(menuChoice, "exit") == 0) {
						head = performProcessing(&head, dispatchProcessing[i].handler);
					}
					// Check if linked list is empty
					else if (head == NULL) {
						printf("No data loaded. Type 'load' to load data from .txt file.\n\n");
					}
					// Perform processing function
					else {
						head = performProcessing(&head, dispatchProcessing[i].handler);
					}
					found = true;
				}
			}

			// Invalid Input
			if (!found) {
				printf("Invalid menu option. Type 'help' for a list of commands.\n\n");
			} 
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
	printf("load:\t\tThis option loads data from a .txt file after you provide the name.\n\t\tIf there is nothing in the file, then data will not be loaded. The maximum line size is 256 characters.\n\n");
	printf("save:\t\tThis option saves any filtered or transformed lines to a file.\n\t\tIf you specify the name of a file that already exists, it will overwrite the data. \n\n");
	printf("------------------------------------------------------\n");
	printf("File Commands:\n");
	printf("------------------------------------------------------\n");
	printf("view:\t\tThis option displays the data loaded from the .txt file.\n\n");
	printf("filter:\t\tThis option allows you to enter one or two keywords to filter the lines of the file.\n\t\tIf one of the keyword(s) is present in the line, the line is deleted.\n\n");
	printf("transform:\tThis option allows you to transform each line of the file depending on a transformation rule:\n\t\tuppercase (u/U), lowercase (l/L), or reverse. (r/R).\n\n");
	printf("summarize:\tThis option allows you to enter a keyword and displays the total number of lines in the file,\n\t\tthe frequency of the keyword you specified, and the average length of each line.\n\n");
	printf("\ntest:\t\tShows testing-related commands.\n");
	printf("\nsecret:\t\tShows secret commands.\n\n");
	printf("exit:\t\tThis option exits the program.\n\n");
}

//
// FUNCTION : test
// DESCRIPTION :
//		 This function prints testing-related commands to the screen.
// PARAMETERS :
//		 void	:	This function does not take any parameters.
// RETURNS :
//		void	:	This function does not return a value.
//
void test(void) {
	printf("input\tEnter 'input' or 'input.txt' in the menu to automatically load input.txt for testing purposes.\n");
	printf("output\tEnter 'output' or 'output.txt' in the menu to automatically save changes to output.txt for testing purposes.\n");
	printf("\tNote about output: 'summarize' provides the option to save to an output file.\n\n");
}

//
// FUNCTION : secret
// DESCRIPTION :
//		 This function prints a secret command to the screen.
// PARAMETERS :
//		 void	:	This function does not take any parameters.
// RETURNS :
//		void	:	This function does not return a value.
//
void secret(void) {
	printf("\tEnter 'kris' in the menu for a secret message.\n");
	printf("\tThere is an extra rule to transform lines: Enter '*' to change every line to 'Glory to Arstotzka.'\n");
}

//
// FUNCTION : kris
// DESCRIPTION :
//		 This function prints a secret message to the screen.
// PARAMETERS :
//		 void	:	This function does not take any parameters.
// RETURNS :
//		void	:	This function does not return a value.
//
void kris(void) {
	printf("Kris Get The Banana.\n\n");
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
	// Check if there is a linked list
	if (head != NULL) {
		// Free dynamically-allocated memory
		free(*head);
	}
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
void performFile(FILE** file, Line** head, char mode[], void (*callback)(FILE*, Line**, char[])) {
	if (callback != NULL) {
		callback(&file, head, mode);
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
Line* performProcessing(Line** head, Line* (*callback)(Line**)) {
	if (callback != NULL) {
		callback(head);
	}
	else {
		printf("Invalid command. Please try again.\n");
	}
}
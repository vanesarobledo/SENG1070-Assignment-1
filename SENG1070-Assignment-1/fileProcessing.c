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
//			char mode[]	:	Mode to open file
// RETURNS :
//			int*		:	Pointer to a file		
//
FILE* loadFile(char mode[]) {
	FILE* file = NULL; // File pointer
	char filename[INPUT_SIZE] = ""; // Name of file
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

	// Open file for reading and writing, or creates the file if it doesn't exist
	file = fopen(filename, mode);
	if (file == NULL) {
		// Exit if there is a failure to open file
		printf("Error opening file. Exiting program...\n");
		exit(EXIT_FAILURE);
	}
	else {
		// Successfully load the file
		printf("%s loaded.\n", filename);
		return file;
	}
}

//
// FUNCTION : storeFileData
// DESCRIPTION :
//			This function takes a file pointer and saves each lline to a linked list of Lines
// PARAMETERS :
//		int* file	:	Pointer to file
// RETURNS :
//		Line*		:	Pointer to a linked list of Lines
//
Line* storeFileData(FILE* file) {
	bool fileEnd = false; // Flag while reading data from file
	char buffer[LINE_SIZE] = ""; // String to store line from file
	char readLine[LINE_SIZE] = ""; // String to store line to add to node
	Line* head = NULL; // Initialize pointer to head of linked list
	Line* newLine = NULL; // Store pointer to new node of linked list

	while (!fileEnd) {
		// Stop reading file if EOF is reached
		if (feof(file)) {
			fileEnd = true;
		}
		// Stop reading file if some file error occurs
		else if (ferror(file)) {
			printf("Error reading file.\n");
			return head;
		}
		else
		{
			// Assign data to Line struct
			fgets(buffer, LINE_SIZE, file);
			// Validate input from file
			if (sscanf(buffer, "%s", &readLine) > 0) {
				// Make sure line isn't empty
				if (strlen(readLine) != 0) {
					strncpy(readLine, buffer, LINE_SIZE);
					// Insert node into linked list
					insertNode(&head, createNode(readLine));
				}
			}
		}
	}

	// Close the file safely
	if (fclose(file) != 0) {
		printf("Error closing file.\n");
		return head;
	}

	// Print if data was loaded from file
	if (head != NULL) {
		printf("Data successfully loaded from file.\n\n");
	}
	else
	{
		printf("No data loaded from file.\n\n");
	}

	return head;
}

//
// FUNCTION : createNode
// DESCRIPTION :
//			Creates a node for the linked list of Lines
// PARAMETERS :
//		char line[]	:	The line to save to the node
// RETURNS :
//		Line*		:	This function returns a pointer to newly-created node
//
Line* createNode(char line[]) {
	// Dynamically allocate a node
	Line* newLine = (Line*)malloc(sizeof(Line));

	// Check if there is enough memory
	if (newLine == NULL) {
		printf("Not enough memory to allocate node.\n");
		exit(EXIT_FAILURE);
	}

	// Assign line to node & set next pointer to NULL
	strncpy(newLine->line, line, LINE_SIZE);
	newLine->next = NULL;

	return newLine;
}
//
// FUNCTION : insertNode
// DESCRIPTION :
//			Adds a node to the tail end of linked list of Lines
// PARAMETERS :
//		Line** head		:	Pointer to head of linked list
//		Line* newLine	:	Node to add to linked list
// RETURNS :
//		int				:	Return code if node was inserted properly
//
int insertNode(Line** head, Line* newLine) {
	// If list is empty, insert node as new head
	if (*head == NULL) {
		*head = newLine;
		return VALID;
	}
	// Iterate through linked list until the tail node is found, then add it to end of linked list
	Line* current = *head;
	while (current->next != NULL) {
		current = current->next;
	}
	current->next = newLine; 

	return VALID;
}

//
// FUNCTION : freeList
// DESCRIPTION :
//			Frees allocated memory of a linked list
// PARAMETERS :
//		Line** head		:	Pointer to head of linked list
// RETURNS :
//		void			:	This function does not return a value
//
void freeList(Line** head) {
	Line* current = *head;
	Line* next;
	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
}

//
// FUNCTION : viewLines
// DESCRIPTION :
//			Views all the nodes of the linked list of Lines
// PARAMETERS :
//		Line* head		:	Pointer to head of linked list
// RETURNS :
//		void			:	This function does not return a value
//
void viewLines(Line* head) {
	Line* current = head;
	while (current != NULL) {
		printf("%s", current->line);
		current = current->next;
	}
	printf("\n\n");
}

//
// FUNCTION : saveFile
// DESCRIPTION :
//			This function saves any changes to file
// PARAMETERS :
//		FILE* file	:	Pointer to file
//		Line** head	:	Pointer to head of linked list of Lines
// RETURNS :
//			int		:	Return code if file was saved properly
//
int saveFile(FILE* file, Line** head) {
	// If list is empty, do not write new data
	if (*head == NULL) {
		printf("No data to write to file.\n");
		return INVALID;
	}
	else
	{
		// Iterate through linked list and write each line
		Line* current = *head;
		while (current != NULL) {
			// Ensure line isn't empty
			if (strlen(current->line) != 0) {
				// Write to file
				if (fprintf(file, "%s", current->line) > 0) {
					current = current->next;
				}
			}
		}
	}
	// Close the file safely
	if (fclose(file) != 0) {
		printf("Error closing file.\n");
		return INVALID;
	}
	else
	{
		return VALID;
	}
}
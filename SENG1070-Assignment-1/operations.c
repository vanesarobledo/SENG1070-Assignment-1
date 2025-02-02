/*
* FILE : operations.c
* PROJECT : SENG1070 Assignment 1
* PROGRAMMER : Vanesa Robledo
* FIRST VERSION : 2025-01-29
* DESCRIPTION :
* 
* This file contains the file processing functions.
*/

#include "operations.h"

// FUNCTION DEFINITIONS


void getKeywords(char* keywords[]) {

}

//
// FUNCTION : filterLines
// DESCRIPTION :
//			This function filters a given list of lines by specified keywords
// PARAMETERS :
//			Line** head	:	Pointer to head of linked list of Lines
// RETURNS :
//			void		:	This function does not return a value
void filterLines(Line** head) {
	char buffer[KEYWORD_SIZE] = ""; // Buffer to store user input
	char keyword[KEYWORD_SIZE] = ""; // Store keyword temporarily
	char keywords[NUMBER_KEYWORDS][KEYWORD_SIZE] = {"", ""}; // Array of keywords
	bool valid = false; // Flag to loop until valid input

	if (head == NULL) {
		printf("No data loaded to filter.\n");
		return;
	}

	for (int i = 0; i < NUMBER_KEYWORDS; i++) {
		valid = false;
		while (!valid) {
			// Prompt the user to enter keyword
			printf("Enter keyword %d: ", i + 1);
			fgets(buffer, KEYWORD_SIZE, stdin);
			// Validate input
			if (sscanf(buffer, "%s", &keyword) == 1) {
				//keywords[i] = keyword;
				strncpy(keywords[i], keyword, KEYWORD_SIZE);
				valid = true;
			}
			else {
				printf("Invalid input, please try again.\n");
			}
		}
	}

	printf("%s\n", keywords[0]);
	printf("%s\n", keywords[1]);

	// Iterate through lines of file
	Line* current = *head;
	Line* next = NULL;

	while (current != NULL) {
		// Check head node first
		if (*head == current) {
			next = current->next;
			// If head contains keyword, delete head and set new head
			if (strstr(current->line, keywords[0]) != NULL || strstr(current->line, keywords[1]) != NULL) {
				*head = next;
				free(current);
			}
			current = next;
		}
		// If next node contains keyword, change pointer of current node to point to next's next
		else if (current->next != NULL) {
			if (strstr(current->next->line, keywords[0]) != NULL || strstr(current->next->line, keywords[1]) != NULL)
			{
				// Store pointer of next node
				next = current->next->next;

				// Delete node of linked list
				free(current->next);

				// Check if next node is tail
				if (next != NULL) {
					// Set pointer of current node to next node if it is not the tail
					current->next = next;
				}
				else
				{
					// If the node is the tail, set pointer of penultimate node to null to be new tail
					current->next = NULL;
				}
			}
			else {
				// Iterate through linked list
				current = next;
			}
		}
		// If at tail node, and there are no keywords, stop iterating
		else if (current->next == NULL) {
			current = NULL;
		}
		// If node does not contain either keyword, move pointer to iterate list
		else {
			current = next;
		}
	}

}


//
// FUNCTION : transformLines
// DESCRIPTION :
//			
// PARAMETERS :
//				
// RETURNS :
//			
//
//void transformLines(char* lines[], char rule[]) {
//
//}

//
// FUNCTION : summarizeLines
// DESCRIPTION :
//			
// PARAMETERS :
//				
// RETURNS :
//			
//
//void summarizeLines(char* lines[], char* keywords[]) {
//
//}
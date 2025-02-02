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

//
// FUNCTION : filterLines
// DESCRIPTION :
//			This function filters a given list of lines by specified keywords
// PARAMETERS :
//			Line** head	:	Pointer to head of linked list of Lines
// RETURNS :
//			void		:	This function does not return a value
//
void filterLines(Line** head) {
	// If linked list is empty, do not check for keywords to filter
	if (head == NULL) {
		printf("No data loaded to filter.\n");
		return;
	}

	char buffer[INPUT_SIZE] = ""; // Buffer to store user input
	char keyword[INPUT_SIZE] = ""; // Store keyword temporarily
	bool valid = false; // Flag to loop until valid input
	char keywords[NUMBER_KEYWORDS][INPUT_SIZE] = { "" }; // Array of keywords

	for (int i = 0; i < NUMBER_KEYWORDS; i++) {
		valid = false;
		while (!valid) {
			// Prompt the user to enter keyword
			printf("Enter keyword %d (case-sensitive): ", i + 1);
			fgets(buffer, INPUT_SIZE, stdin);
			// Validate input
			if (sscanf(buffer, "%s", &keyword) == 1) {
				strncpy(keywords[i], keyword, INPUT_SIZE);
				valid = true;
			}
			else {
				printf("Invalid input, please try again.\n");
			}
		}
	}

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
//			This function accepts a list of lines and transforms them based on a transformation rule:
//			UPPERCASE (u), lowercase (l), or reverse (r)
// PARAMETERS :
//			Line** head	:	Pointer to head of linked list of Lines
//			char[] rule	:	The transformation rule to be applied to each line
// RETURNS :
//			void	:	This function does not return a value.
//
void transformLines(Line** head, char rule) {
	// If linked list is empty, do not transform lines
	if (*head == NULL) {
		printf("No data loaded to transform.\n");
		return;
	}

	// Iterate through linked list
	Line* current = *head;
	Line* next = NULL;

	while (current != NULL) {
		switch (rule)
		{
			// Upercase transformation
			case 'u':
			case 'U':
				strncpy(current->line, strupr(current->line), LINE_SIZE);
				break;
			// Reverse transformation
			case 'r':
			case 'R':
				strncpy(current->line, strrev(current->line), LINE_SIZE);
				break;
			// Lowercase transformation
			case 'l':
			case 'L':
				strncpy(current->line, strlwr(current->line), LINE_SIZE);
				break;
			// Secret transformation
			case '*':
				strncpy(current->line, "Glory to Arstozska\n", LINE_SIZE);
				break;
			default:
				printf("Invalid option selected.\n");
				break;
		}
		current = current->next;
	}

}

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



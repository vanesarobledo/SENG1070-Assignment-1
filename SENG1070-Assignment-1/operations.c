/*
* FILE : operations.c
* PROJECT : SENG1070 Assignment 1
* PROGRAMMER : Vanesa Robledo
* FIRST VERSION : 2025-01-29
* DESCRIPTION :
* This program allows for file processing operations - filtering, transforming, summarizing -
* and saving the changes to a file.
* This file contains the file processing functions.
*/

#include "operations.h"
// Use non-secure functions
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS	1
#endif

//
// FUNCTION : viewLines
// DESCRIPTION :
//			Views all the nodes of the linked list of Lines
// PARAMETERS :
//		Line** head		:	Pointer to head of linked list
// RETURNS :
//		void			:	This function does not return a value
//
void viewLines(Line** head) {
	// Check if linked list is empty
	if (*head == NULL) {
		printf("No data loaded. Type 'load' to load data from .txt file.\n\n");
		return;
	}

	Line* current = *head;
	while (current != NULL) {
		printf("%s", current->line);
		current = current->next;
	}

	printf("\n\n");
}


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
	if (*head == NULL) {
		printf("No data loaded to filter.\n");
		return;
	}

	// Get keywords from user
	// Note: Returning strings in C is a pain, even moreso an array of stringgs
	// For modularity, this should be its own function
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

	// Iterate through lines
	Line* current = *head;
	Line* next = NULL;

	int lineCount = 0; // Keep track of the total number of lines
	int deletedLines = 0; // Keep track of the number of deleted lines

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
			// Check tail node and free tail node memory
			else if (current->next == NULL) {
				if (strstr(current->next->line, keywords[0]) != NULL || strstr(current->next->line, keywords[1]) != NULL)
				{
					free(current);
				}
			}
			else {
				// Iterate through linked list
				current = next;
			}
		}
		// If node does not contain either keyword, move pointer to iterate list
		else {
			current = next;
		}
	}

	if (*head != NULL) {
		printf("\n------------------------------------------------------\n");
		printf("Filtered Lines (Keywords: '%s' and '%s'):\n", keywords[0], keywords[1]);
		printf("------------------------------------------------------\n");

		viewLines(head);
	}
	// All lines were filtered
	else {
		head = NULL;
		printf("All lines containing keywords: '%s' and '%s' were filtered.\n\n", keywords[0], keywords[1]);
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
void transformLines(Line** head) {
	// If linked list is empty, do not transform lines
	if (head == NULL) {
		printf("No data loaded to transform.\n");
		return;
	}

	char transformationChoice = '\0'; // User choice for transformation rule
	bool validTransform = false; // Flag to loop transformation rule

	// Prompt user for transformation rule
	while (!validTransform) {
		printf("Select transformation rule:\n");
		printf("Uppercase (U or u)\n");
		printf("Lowercase (L or l)\n");
		printf("Reverse (R or r)\n");
		transformationChoice = menuChoice();
		switch (transformationChoice)
		{
		case 'u':
		case 'U':
		case 'l':
		case 'L':
		case 'r':
		case 'R':
		case '*':
			validTransform = true;
			break;
		default:
			printf("Invalid transformation rule. Please try again.\n");
			break;
		}
	}

	// Iterate through linked list
	Line* current = *head;

	while (current != NULL) {
		switch (transformationChoice)
		{
			// Upercase transformation
			case 'u':
			case 'U':
				strncpy(current->line, _strupr(current->line), LINE_SIZE);
				break;
			// Reverse transformation
			case 'r':
			case 'R':
				strncpy(current->line, _strrev(current->line), LINE_SIZE);
				break;
			// Lowercase transformation
			case 'l':
			case 'L':
				strncpy(current->line, _strlwr(current->line), LINE_SIZE);
				break;
			// Secret transformation
			case '*':
				strncpy(current->line, "Glory to Arstotzka\n", LINE_SIZE);
				break;
			default:
				printf("Invalid option selected.\n");
				break;
		}
		current = current->next;
	}

	printf("\n------------------------------------------------------\n");
	printf("Transformed Lines: ");
	switch (transformationChoice)
	{
	case 'u':
	case 'U':
		printf("Uppercase\n");
		break;
	case 'r':
	case 'R':
		printf("Reverse\n");
		break;
	case 'l':
	case 'L':
		printf("Lowercase\n");
		break;
	case '*':
		printf("Glory to Arstotzka\n");
		break;
	default:
		printf("");
	}
	printf("------------------------------------------------------\n");

	viewLines(head);

	return;
}

//
// FUNCTION : summarizeLines
// DESCRIPTION :
//			This function allows the user to enter a keyword and displays the total number of lines in the file,
//			the frequency of the keyword specified, and the average length of each line.
// PARAMETERS :
//			Line** head	:	Pointer to head of linked list of Lines
// RETURNS :
//			void	:	This function does not return a value.
//
void summarizeLines(Line** head) {
	// If linked list is empty, do not summarize lines
	if (head == NULL) {
		printf("No data loaded to summarize.\n");
		return;
	}

	// Get keyword
	char buffer[INPUT_SIZE] = ""; // Buffer to store user input
	char keyword[INPUT_SIZE] = ""; // Store keyword
	bool valid = false; // Flag to loop until valid input

	while (!valid) {
		// Prompt the user to enter keyword
		printf("Enter keyword to search (case-insensitive): ");
		fgets(buffer, INPUT_SIZE, stdin);
		// Validate input
		if (sscanf(buffer, "%s", &keyword) == 1) {
			valid = true;
		}
		else {
			printf("Invalid input, please try again.\n");
		}
	}

	// Iterate through lines of file
	Line* current = *head;

	// Initialize data
	int lineCount = 0;
	int lineLength = 0;
	int lineLengthSum = 0;
	double lineLengthAverage = 0.0;

	// Data needed for keyword search
	int keywordFrequency = 0;

	// Iterator variables for keywords
	int keywordLength = (int)strlen(keyword);
	int lineIterator;
	int keywordIterator;
	int keywordCharacterCount = 0;

	// Convert line and keyword to lowercase to be case-insensitive
	char transformedLine[LINE_SIZE];
	char transformedKeyword[LINE_SIZE];
	strncpy(transformedKeyword, _strlwr(keyword), LINE_SIZE);
	transformedKeyword[keywordLength] = '\0';

	while (current != NULL) {
		// Add to line count
		lineCount++;
		
		// Count frequency of keyword:

		// Store line length
		lineLength = (int)strlen(current->line);

		// Comnvert line to lowercase
		strncpy(transformedLine, current->line, LINE_SIZE);
		transformedLine[lineLength] = '\0'; // Ensure null-termination
		_strlwr(transformedLine); // Transform to lowercase to match keyword

		// Check if keyword exists in string
		// Algorithm used: 
		/*
		* TITLE : C Program to Count the Occurrence of a Substring in String
		* AUTHOR : Manish Bhojasia
		* DATE : unknown
		* VERSION : 1.0
		* AVAILABIILTY : https://www.sanfoundry.com/c-program-count-occurrence-substring/
		*/
		if (strstr(transformedLine, transformedKeyword) != NULL) {
			for (lineIterator = 0; lineIterator  < lineLength;) {
				keywordIterator = 0;
				// Compare each character of lines (case-insensitive)
				while ((transformedLine[lineIterator] == transformedKeyword[keywordIterator] )) {
					lineIterator++;
					keywordCharacterCount++;
					keywordIterator++;
				}
				if (keywordCharacterCount == keywordLength) {
					keywordFrequency++;
				}
				else {
					lineIterator++;
				}
				keywordCharacterCount = 0;
			}
		}
		
		// Add length of string to line length sum
		lineLengthSum += lineLength;

		current = current->next;
	}

	lineLengthAverage = (double)lineLengthSum / (double)lineCount;

	// Print summary to screen
	printf("------------------------------------------\n");
	printf("Summary:\n");
	printf("Total Number of Lines: %d\n", lineCount);
	if (keywordFrequency == 0) {
		printf("No instances of '%s' found.\n", keyword);
	}
	else if (keywordFrequency == 1) {
		printf("Frequency of '%s': %d time\n", keyword, keywordFrequency);
	}
	else {
		printf("Frequency of '%s': %d times\n", keyword, keywordFrequency);
	}
	printf("Average Length of Lines: %.2f characters\n", lineLengthAverage);
	printf("------------------------------------------\n\n");

}

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
	char charInput = '\0'; // Variable to store character
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
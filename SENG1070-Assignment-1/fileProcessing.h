#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// DEFINE CONSTANTS

// Define buffer and string sizes
#define	INPUT_SIZE	100
#define	LINE_SIZE	200
#define	NUMBER_KEYWORDS	2

// Define return codes
#define	VALID	0
#define	INVALID	-1

// Define struct to store file lines
typedef struct Line {
	char line[LINE_SIZE];
	struct Line* next;
} Line;

// FUNCTION PROTOYPES

// File Functions
FILE* loadFile(char[]);
Line* storeFileData(FILE*);
int saveFile(FILE*, Line**);

// Linked List Functions
Line* createNode(char[]);
int insertNode(Line**, Line*);
void freeList(Line**);
void viewLines(Line*);
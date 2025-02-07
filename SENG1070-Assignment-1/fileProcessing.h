#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Use non-secure functions
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS	1
#endif

// DEFINE MACROS

// Define buffer and string sizes
#define	INPUT_SIZE	256
#define	CHAR_SIZE	3
#define	LINE_SIZE	256
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
void loadFile(FILE*, Line**, char[]);
void saveFile(FILE*, Line**, char[]);
Line* storeFileData(FILE*);

// Linked List Functions
Line* createNode(char[]);
int insertNode(Line**, Line*);
void freeList(Line**);
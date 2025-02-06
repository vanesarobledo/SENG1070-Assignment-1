#include <stdio.h>
#include <string.h>
#include <ctype.h> // for line transformation functions
#pragma once
// Use non-secure functions
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS	1
#endif

#include "fileProcessing.h"

// FUNCTION PROTOTYPES
Line* filterLines(Line**);
Line* transformLines(Line**);
Line* summarizeLines(Line**);
Line* viewLines(Line**);
char menuChoice(void);
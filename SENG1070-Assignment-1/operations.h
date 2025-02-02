#include <stdio.h>
#include <string.h>
#include <ctype.h> // for line transformation functions
#pragma once

#include "fileProcessing.h"

// FUNCTION PROTOTYPES
void filterLines(Line**);
void transformLines(Line**);
void summarizeLines(Line**);
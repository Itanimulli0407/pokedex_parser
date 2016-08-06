#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef EXTRACTOR_H
#define EXTRACTOR_H

extern char* extractNameFromReferenceLine(char[]);

extern char* extractNameFromNonReferencedLine(char[]);

extern char* extractNumber(char[]);

extern char* extractNumberFromReferencedLine(char[]);

extern char* extractTypes(char[]);

#endif /*EXTRACTOR_H*/

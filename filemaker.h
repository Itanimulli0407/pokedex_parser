#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#ifndef FILEMAKER_H
#define FILEMAKER_H

extern void createOrReplaceFile();

extern void insertFirstNumber(char*);

extern void insertNumber(char*);

extern void insertName(char*);

extern void insertEnglishName(char*);

extern void insertFirstType(char*);

extern void insertSecondType(char*);

extern void closeFile();

#endif /*FILEMAKER_H*/

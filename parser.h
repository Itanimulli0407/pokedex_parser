#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "filemaker.h"
#include "extractor.h"

#ifndef PARSER_H
#define PARSER_H

int match(regex_t*, char*);

int parsePokedex(char* filepath);

int parseAttacks(char* filepath);

#endif /*PARSER_H*/

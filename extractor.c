#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "extractor.h"

char* extractNameFromReferenceLine(char line[500]){
  char delimiter[] = "><";
  char *word;
  word = strtok(line, delimiter);
  for (int i = 0; i<3; i++){
    word = strtok(NULL, delimiter);
  }
  return word;
}

char* extractNumber(char line[500]){
  char delimiter[] = ">< ";
  char *word;
  word = strtok(line, delimiter);
  word = strtok(NULL, delimiter);
  return word;
}

char* extractNumberFromReferencedLine(char line[500]){
  char delimiter[] = ">< ";
  char *word;
  word = strtok(line, delimiter);
  for (int i = 0; i<4; i++){
    word = strtok(NULL, delimiter);
  }
  return word;
}

char* extractNameFromNonReferencedLine(char line[500]){
  char delimiter[] = ">< ";
  char *word;
  word = strtok(line, delimiter);
  word = strtok(NULL, delimiter);
  return word;
}

char* extractTypes(char line[500]){
  char delimiter[] = "><";
  char *word;
  char *output;
  strcat(line, "< > < > < > < > < > < > < >");
  word = strtok(line, delimiter);
  for (int i = 0; i<6; i++){
    word = strtok(NULL, delimiter);
  }
  output = word;
  for (int i = 0; i<7; i++){
    word = strtok(NULL, delimiter);
  }
  output = strcat(output, " ");
  output = strcat(output, word);
  return output;
}

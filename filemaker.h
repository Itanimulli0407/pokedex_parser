#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

FILE *file;

void createOrReplaceFile(){
  FILE *file = fopen("pokedex.txt", "wb+");
  fputs("INSERT INTO pokedex VALUES\n", file);
}

void createValue(char* number, char* name, char* englishName, char* type1,
    char* type2){
  char* buffer;
  snprintf(buffer, sizeof buffer, ",(%s,'%s','%s','%s','%s')\n", number, name, englishName, type1, type2);
  fputs(buffer, file);
}

void closeFile(){
  fputs(";", file);
  fclose(file);
}

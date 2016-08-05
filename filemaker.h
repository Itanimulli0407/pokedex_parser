#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

FILE *sqlfile;

char* value;

void createOrReplaceFile(){
  sqlfile = fopen("pokedex.txt", "wb+");
  fprintf(sqlfile, "INSERT INTO pokedex VALUES\n");
}

void insertFirstNumber(char* number){
  fprintf(sqlfile, "(%s,", number);
}

void insertNumber(char* number){
  fprintf(sqlfile, ",(%s,", number);
}

void insertName(char* name){
  fprintf(sqlfile, "\'%s\',", name);
}

void insertEnglishName(char* englishName){
  fprintf(sqlfile, "\'%s\',", englishName);
}

void insertFirstType(char* type1){
  fprintf(sqlfile, "\'%s\',", type1);
}

void insertSecondType(char* type2){
  if (strcmp(type2,"NULL") == 0){
    fprintf(sqlfile, "NULL)\n");
  } else {
    fprintf(sqlfile, "\'%s\')\n", type2);
  }
}

void closeFile(){
  fprintf(sqlfile, ";");
  fclose(sqlfile);
}

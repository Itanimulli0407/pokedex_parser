#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

FILE *file;

char* value;

void createOrReplaceFile(){
  FILE *file = fopen("pokedex.txt", "wb+");
  fputs("INSERT INTO pokedex VALUES\n", file);
}

void createNewValue(){
  value = ",(";
}

void insertNumber(char* number){
  strcat(value, number);
}

void insertName(char* name){
  strcat(strcat(strcat(value, ",'"),name),"',");
}

void insertEnglishName(char* englishName){
  strcat(strcat(strcat(value, "'"),englishName),"',");
}

void insertFirstType(char* type){
  strcat(strcat(strcat(value, "'"),type),"',");
}

void insertSecondType(char* type){
  strcat(strcat(strcat(value, "'"),type),"'");
}

void closeValue(){
  strcat(value, ")\n");
  fputs(value, file);
}

void closeFile(){
  fputs(";", file);
  fclose(file);
}

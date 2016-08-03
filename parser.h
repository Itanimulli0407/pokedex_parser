#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "filemaker.h"

int match(regex_t *pexp, char *sz) {
  int MAX_MATCHES = 1;
	regmatch_t matches[MAX_MATCHES]; //A list of the matches in the string (a list of 1)
	//Compare the string to the expression
	//regexec() returns 0 on match, otherwise REG_NOMATCH
	if (regexec(pexp, sz, MAX_MATCHES, matches, 0) == 0) {
		return 1;
	} else {
		return 0;
	}
}

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
  char delimiter[] = "><";
  char *word;
  word = strtok(line, delimiter);
  word = strtok(NULL, delimiter);
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

int parseFile (char *filepath) {
  FILE *file;
  char line[500];

  file = fopen(filepath, "r");

  createOrReplaceFile();

	regex_t expEnglishName;
  regex_t expGermanName;
  regex_t expNumber;
  regex_t expType;
  // Compile the expressions for names of pokemon
	regcomp(&expEnglishName, "<td> [A-Z,a-z2()]* </td>", REG_EXTENDED);
  regcomp(&expGermanName, "<td> <a href=\"/[A-Z,a-z2()]*\" title=\"[A-Z,a-z2()]*\">[A-Z,a-z2()]*</a> </td>.", REG_EXTENDED);
  regcomp(&expNumber, "<td> [0-9][0-9][0-9] </td>", REG_EXTENDED);
  regcomp(&expType, "<td> <a href=\"/.*\" title=\".*\"><img alt=.*" , REG_EXTENDED);

  // Parse the file with regex-matching
  int lan_flag = 1; // 1:german, 2:english, 3:french, 4:japanese, 5: korean
  int a = 1; // counter for first x pokemon;

  char* number;
  char* name;
  char* englishName;
  char* types;
  char* type1;
  char* type2;

  while(fgets(line, 500, file) && a<152){
    if(match(&expEnglishName, line)){
      lan_flag++;
      if (lan_flag == 2){
        englishName = extractNameFromNonReferencedLine(line);
        insertEnglishName(englishName);
        //pkm.englishName = &englishName;
        printf("Englisch: %s -- ", englishName);
        a++;
      }
    } else if(match(&expGermanName, line)){
      name = extractNameFromReferenceLine(line);
      insertName(name);
      printf("Deutsch: %s -- ", name);
      //pkm.name = &name;
      lan_flag = 1;
    } else if(match(&expNumber, line)){
      createNewValue();
      number = extractNumber(line);
      insertNumber(number);
      //pkm.number = &number;
      printf("%s -- ", number);
    } else if(match(&expType, line)){
      types = extractTypes(line);
      type1 = strtok(types, " ");
      type2 = strtok(NULL, " ");
      if (type2 == NULL){
        type2 = "NULL";
      }
      insertFirstType(type1);
      insertSecondType(type2);
      //pkm.type1 = &type1;
      //pkm.type2 = &type2;
      printf("%s -- %s\n", type1, type2);

//printf("%s+\n", name);
      //Special case for Bulbasaur
      //if (strcmp(name, "Bisasam") == 0){
      //  number = "001";
      //}
      //CREATE SQL Statement
      //createValue(number, name, englishName, type1, type2);
      closeValue();
    }
  }

  regfree(&expEnglishName);
  regfree(&expGermanName);
  regfree(&expNumber);
  regfree(&expType);

  // Complete the SQL Statement
  //closeFile();
  // Close the pokedex file
  fclose(file);

  return 0;
}

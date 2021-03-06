#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "parser.h"

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

int parsePokedex (char *filepath) {
  FILE *file;
  char line[500];

  file = fopen(filepath, "r");

  createOrReplaceFile();

	regex_t expEnglishName;
  regex_t expGermanName;
  regex_t expNumber;
  regex_t expNumberReferenced;
  regex_t expType;

  // Compile the expressions for names of pokemon
	regcomp(&expEnglishName, "<td> [A-Z,a-z2()-]* </td>", REG_EXTENDED);
  regcomp(&expGermanName, "<td> <a href=\"/[A-Z,a-z2()-]*\" title=\"[A-Z,a-z2()-]*\">[A-Z,a-z2()-]*</a> </td>.", REG_EXTENDED);
  regcomp(&expNumber, "<td> [0-9]* </td>", REG_EXTENDED);
  regcomp(&expNumberReferenced, "<td> <span id=\".*\"></span>.*</td>", REG_EXTENDED);
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

  while(fgets(line, 500, file) && a<387){
    if (a > 0){
      if(match(&expEnglishName, line)){
        lan_flag++;
        if (lan_flag == 2){
          englishName = extractNameFromNonReferencedLine(line);
          insertEnglishName(englishName);
          printf("Englisch: %s -- ", englishName);
        }
      } else if(match(&expGermanName, line)){
        name = extractNameFromReferenceLine(line);
        // I have no clue why corasonn doesn't work
        if (strcmp(name, "Corasonn") == 0){
          insertNumber("222");
        }
        insertName(name);
        printf("Deutsch: %s -- ", name);
        lan_flag = 1;
      } else if(match(&expNumber, line)){
        number = extractNumber(line);
        printf("%s -- ", number);
        insertNumber(number);
      } else if (match(&expNumberReferenced, line)){
        number = extractNumberFromReferencedLine(line);
        printf("%s -- ", number);
        if (strcmp(number, "001") == 0){
          insertFirstNumber(number);
        } else {
          insertNumber(number);
        }
      } else if(match(&expType, line)){
        types = extractTypes(line);
        type1 = strtok(types, " ");
        type2 = strtok(NULL, " ");
        if (type2 == NULL){
          type2 = "NULL";
        }
        insertFirstType(type1);
        insertSecondType(type2);
        printf("%s -- %s\n", type1, type2);
        a++;
      }
    }
  }

  regfree(&expEnglishName);
  regfree(&expGermanName);
  regfree(&expNumber);
  regfree(&expNumberReferenced);
  regfree(&expType);

  // Complete the SQL Statement
  closeFile();
  // Close the pokedex file
  fclose(file);

  return 0;
}

int parseAttacks(char* filepath){
  return 0;
}

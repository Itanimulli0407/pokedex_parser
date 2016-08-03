#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

int main (int argc, char *argv[]){
  if (argc > 2){
    printf("Too many arguments. Please insert only one argument \n");
    return 1;
  } else if (argc < 2){
    printf("Pokedex file is missing. Please insert filepath as argument \n");
    return 1;
  } else {
    printf("Started parsing \n");
    parseFile(argv[1]);
    printf("Parsing done\n");
  }
  return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "strings.h"
#include "run.h"


int main()
{
  while(true) {
    // read the command
    char command[4096]; // "allocate" space for the command
    printf(PS1);
    fgets(command, 4096, stdin);
    int l = strlen(command);
    if(command[l-1] == '\n')
      command[l-1] = '\0';
    if(command[0] == '\0')
      continue; // empty command, re-read command

    // check for builtins
    if(strcmp(command, EXIT) == 0)
      break;

    // run the command
    run(command);
  }
  return 0;
}

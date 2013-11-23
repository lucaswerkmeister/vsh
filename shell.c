#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "strings.h"
#include "run.h"
#include "builtins.h"

int main()
{
  init_builtins();

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

    // handle builtins
    for(int i=0; builtins[i] != NULL; i++) {
      Builtin *builtin = builtins[i];
      if(strcmp(command, builtin->name) == 0) {
        builtin->command();
        goto continue_mainloop;
      }
    }

    // run the command
    run(command);
    
  continue_mainloop:;
  }
  return 0;
}

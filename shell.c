#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "shell.h"
#include "strings.h"
#include "run.h"
#include "builtins.h"

char** read_arguments() {
  char argument[4096]; // buffer
  char** arguments = malloc(4096);
  int i = 0; // index into arguments
  do {
    printf(PS2);
    fgets(argument, 4096, stdin);
    if(argument[0] != '\0') {
      size_t length = strlen(argument);
      if(argument[length-1] == '\n') {
        argument[length-1]='\0';
        length--;
      }
      if(length == 0) {
        arguments[i] = NULL;
        break;
      }
      arguments[i] = malloc(sizeof(char) * (length + 1));
      strncpy(arguments[i], argument, length + 1);
      i++;
    }
  } while(argument[0] != '\0' && i < 4096);
  return arguments;
}

int main()
{
  init_builtins();

  while(true) {
    // read the command
    char command[4096]; // buffer
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
        char** argv;
        if(builtin->takes_arguments) {
          argv = read_arguments();
        } else {
          char* noargs[] = { NULL };
          argv = noargs;
        }
        builtin->command(argv);
        goto continue_mainloop;
      }
    }

    // run the command
    char** argv = read_arguments();
    run(command, argv);
    free(argv);
    
  continue_mainloop:;
  }
  return 0;
}

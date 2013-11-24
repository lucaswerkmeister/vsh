#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

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

void on_sigint(/* int signal */) {
  // print a newline after the ^C
  printf("\n");
}

int main()
{
  init_builtins();
  
  // signal handling:
  // The default way to handle signals is signal(2),
  // but the manpage advises against its use
  // and recommends using sigaction(2) instead.
  // However, this requires the use of
  // -std=gnu99 instead of -std=c99.
  struct sigaction act;
  act.sa_handler = on_sigint;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;
  if( sigaction(SIGINT, &act, NULL) == -1) {
    printf(ERROR_SIGINT_HANDLER, errno, strerror(errno));
  }
  
  while(true) {
    // print PS1
    char* cwd = get_current_dir_name();
    char hostname[256];
    gethostname(hostname, 256);
    printf(PS1, getenv("USER"), getuid(), hostname, cwd);
    free(cwd);

    // read the command
    char command[4096]; // buffer
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
    for(int i=0; argv[i] != NULL; i++) {
      free(argv[i]);
    }
    free(argv);
    
  continue_mainloop:;
  }
  return 0;
}

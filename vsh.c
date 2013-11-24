#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "vsh.h"
#include "strings.h"
#include "run.h"
#include "builtins.h"


HISTORY_STATE *command_history, *argument_history;

char** read_arguments() {
  char** arguments = malloc(4096);
  int i = 0; // index into arguments
  char* argument; // current argument
  history_set_history_state(argument_history);
  do {
    argument = readline(PS2);
    if(argument == NULL)
      // user entered EOF on empty line
      printf("\n");
    if(argument != NULL && argument[0] == '\0')
      argument = NULL;
    arguments[i] = argument;
    i++;
    if(argument != NULL)
      add_history(argument);
  } while(argument != NULL && i < 4096);
  argument_history = history_get_history_state();
  return arguments;
}

void on_sigint(/* int signal */) {
  // print a newline after the ^C
  printf("\n");
}

int main()
{
  init_builtins();

  using_history();
  argument_history = history_get_history_state();
  using_history();
  command_history = history_get_history_state();
  
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
    char* ps1;
    asprintf(&ps1, PS1, getenv("USER"), getuid(), hostname, cwd); // "print" PS1 to string ps1
    free(cwd);

    // read the command
    history_set_history_state(command_history);
    char* command = readline(ps1);
    free(ps1);
    if(command == NULL) {
      command = "";
      printf("\n");
    }
    if(command[0] == '\0')
      continue; // empty command, re-read command
    add_history(command);
    command_history = history_get_history_state();

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

    free(command);
    
  continue_mainloop:;
  }
  return 0;
}

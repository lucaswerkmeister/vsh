#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "run.h"


void run(char* command, char* argv[]) {
  // check if the file exists
  if(access(command, X_OK) != 0) {
    printf("Command not found or permission denied\n");
    return;
  }

  // run
  pid_t process;
  if( (process = fork()) ) {
    int status = 0;
    waitpid(process, &status, 0);
    printf("Command exited with status %d\n", WEXITSTATUS(status));
  } else {
    size_t argc = 0;
    while(argv[argc] != NULL)
      argc++;
    char** new_argv = malloc(argc + 2);
    new_argv[0] = command;
    int i = 0;
    for(; argv[i]!=NULL; i++) {
      new_argv[i+1] = argv[i];
    }
    new_argv[i+1] = NULL;
    errno = 0;
    execvp(command, new_argv);
    // only executed if execution failed:
    printf("Executing command \"%s\" failed due to error: %s\n", command, strerror(errno));
    exit(-1);
  }
}

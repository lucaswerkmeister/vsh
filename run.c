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
    waitpid(process, NULL, 0);
  } else {
    size_t size = 0;
    for(int i=0; argv[i]!=NULL; i++) {
      size += strlen(argv[i]);
    }
    size += strlen(command);
    char** new_argv = malloc(size);
    new_argv[0] = command;
    int i=0;
    for(i=0; argv[i]!=NULL; i++) {
      new_argv[i+1] = argv[i];
    }
    execvp(command, new_argv);
    // only executed if execution failed:
    printf("Executing command \"%s\" failed due to error: %s\n", command, strerror(errno));
    exit(-1);
  }
}

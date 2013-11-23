#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "run.h"


void run(char* command) {
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
    execl(command, command, (char*) NULL);
    // only executed if execution failed:
    printf("Executing command \"%s\" failed due to error: %s\n", command, strerror(errno));
    exit(-1);
  }
}

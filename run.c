#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "run.h"


void run(char* command) {
  pid_t process;
  if( (process = fork()) ) {
    waitpid(process, NULL, 0);
  } else {
    execl(command, command, (char*) NULL);
  }
}

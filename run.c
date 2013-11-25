#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "run.h"
#include "strings.h"


void run(char* command, char* argv[]) {
  // run
  time_t start, stop;
  time(&start);
  pid_t process;
  if( (process = fork()) ) {
    int status = 0;
    waitpid(process, &status, 0);
    time(&stop);
    time_t elapsed = stop - start;
    int hours = elapsed/(60*60);
    int minutes = (elapsed%(60*60))/60;
    int seconds = elapsed%60;
    printf(COMMAND_EXIT, command, WEXITSTATUS(status), hours, minutes, seconds);
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
    printf(COMMAND_FAILED, command, errno, strerror(errno));
    exit(-1);
  }
}

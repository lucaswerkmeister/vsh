#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "builtins.h"

void builtin_exit(char* argv[]) {
  // unused
  (void) argv;
  _exit(0);
}
Builtin b_exit;

Builtin *builtins[] = { &b_exit, NULL }; 

void init_builtins() {
  b_exit.name = EXIT;
  b_exit.takes_arguments = false;
  b_exit.command = &builtin_exit;
}

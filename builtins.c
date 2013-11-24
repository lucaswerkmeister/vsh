#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "builtins.h"

/*
 * sets up `builtin` as an alias of `target`.
 *
 * More specifically
 */
void alias(Builtin *builtin, const char* name, Builtin *target) {
  builtin->name = name;
  builtin->takes_arguments = target->takes_arguments;
  builtin->command = target->command;
}

void builtin_exit(char* argv[]) {
  // unused
  (void) argv;
  _exit(0);
}
Builtin b_exit;
Builtin b_quit;

Builtin *builtins[] = { &b_exit, &b_quit, NULL }; 

void init_builtins() {
  b_exit.name = BUILTIN_EXIT;
  b_exit.takes_arguments = false;
  b_exit.command = &builtin_exit;

  alias(&b_quit, BUILTIN_QUIT, &b_exit);
}

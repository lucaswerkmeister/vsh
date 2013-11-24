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

void builtin_cd(char* argv[]) {
  chdir(argv[0]);
}
Builtin b_cd;
Builtin b_change_directory;

Builtin *builtins[] = { &b_exit, &b_quit, &b_cd, &b_change_directory, NULL }; 

void init_builtins() {
  b_exit.name = BUILTIN_EXIT;
  b_exit.takes_arguments = false;
  b_exit.command = &builtin_exit;

  alias(&b_quit, BUILTIN_QUIT, &b_exit);

  b_cd.name = BUILTIN_CD;
  b_cd.takes_arguments = true;
  b_cd.command = &builtin_cd;

  alias(&b_change_directory, BUILTIN_CHANGE_DIRECTORY, &b_cd);
}

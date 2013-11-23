#ifndef BUILTINS_H
#define BUILTINS_H

#include <stdbool.h>

#include "strings.h"


void builtin_exit(char *argv[]);

typedef struct {
  const char* name;
  bool takes_arguments;
  void (*command)(char *argv[]);
} Builtin;

Builtin b_exit;

void init_builtins(void);

extern Builtin *builtins[];

#endif

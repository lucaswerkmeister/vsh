#ifndef BUILTINS_H
#define BUILTINS_H

#include <stdbool.h>

#include "strings.h"


typedef struct {
  const char* name;
  bool takes_arguments;
  void (*command)(char *argv[]);
} Builtin;

/*
 * initialize the builtins array (see below)
 */
void init_builtins(void);

extern Builtin *builtins[];

#endif

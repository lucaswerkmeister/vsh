#ifndef BUILTINS_H
#define BUILTINS_H

#include "strings.h"

void builtin_exit(void);

typedef struct {
  const char* name;
  void (*command)(void);
} Builtin;

Builtin b_exit;

void init_builtins(void);

extern Builtin *builtins[];

#endif

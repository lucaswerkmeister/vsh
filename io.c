#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "io.h"
#include "strings.h"


char* ps1() {
  char* cwd = get_current_dir_name();
  char hostname[256];
  gethostname(hostname, 256);
  char* ps1;
  asprintf(&ps1, PS1, getenv("USER"), getuid(), hostname, cwd); // "print" PS1 to string ps1
  free(cwd);
  return ps1;
}

char* ps2() {
  char* ps2;
  asprintf(&ps2, PS2);
  return ps2;
}

#ifndef IO_H
#define IO_H

/*
 * Fill in the fields of PS1 (see strings.h).
 *
 * The returned char* should be free()d by the caller.
 */
char* ps1();

/*
 * Fill in the fields of PS2 (see strings.h).
 *
 * The returned char* should be free()d by the caller.
 */
char* ps2(char* command);

#endif

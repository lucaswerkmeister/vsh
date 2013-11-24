#ifndef STRINGS_H
#define STRINGS_H

/*
 * Printed before a command is read.
 */
const char* PS1;

/*
 * Printed before an argument is read.
 */
const char* PS2;

/*
 * Printed if the command file was not found or is not executable
 */
const char* COMMAND_NOT_FOUND;

/*
 * Printed after the command exits.
 *
 * printf parameters: command string, elapsed hours, elapsed minutes, elapsed seconds
 */
const char* COMMAND_TIME;

/*
 * Printed after the command exits.
 *
 * printf parameters: exit status
 */
const char* COMMAND_EXIT;

/*
 * Printed if executing the command failed.
 *
 * printf parameters: command, strerror
 */
const char* COMMAND_FAILED;

/*
 * The builtin command that will exit the shell.
 */
const char* EXIT;

/*
 * An alias to EXIT.
 */
const char* QUIT;

#endif

#ifndef STRINGS_H
#define STRINGS_H

/*
 * Printed if the SIGINT handler can't be registered.
 *
 * printf parameters:
 * 1. errno
 * 2. strerror(errno)
 */
const char* ERROR_SIGINT_HANDLER;

/*
 * Printed before a command is read.
 *
 * printf parameters:
 * 1. user name
 * 2. user ID
 * 3. hostname
 * 4. current working directory
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
 * printf parameters:
 * 1. command string
 * 2. exit status
 * 3. elapsed hours
 * 4. elapsed minutes
 * 5. elapsed seconds
 */
const char* COMMAND_EXIT;

/*
 * Printed if executing the command failed.
 *
 * printf parameters:
 * 1. command
 * 2. errno
 * 3. strerror(errno)
 */
const char* COMMAND_FAILED;

/*
 * The builtin command that will exit the shell.
 */
const char* BUILTIN_EXIT;

/*
 * An alias to BUILTIN_EXIT.
 */
const char* BUILTIN_QUIT;

/*
 * The builtin command that changes the current directory.
 */
const char* BUILTIN_CD;

/*
 * An alias to BUILTIN_CD.
 */
const char* BUILTIN_CHANGE_DIRECTORY;

#endif

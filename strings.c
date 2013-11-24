#include "strings.h"


const char* ERROR_SIGINT_HANDLER = "WARNING: Could not register SIGINT handler; error: %2$s\n";

#ifdef EXPERT
const char* PS1 = "%1$s@%3$s %4$s $ ";
const char* PS2 = "> ";
#else
const char* PS1 = "Enter a command: ";
const char* PS2 = "Enter an argument, or nothing to end arguments: ";
#endif

const char* COMMAND_NOT_FOUND = "Command not found or permission denied\n";

const char* COMMAND_EXIT = "Command exited with status %2$d after %3$02d:%4$02d:%5$02d\n";

const char* COMMAND_FAILED = "Executing command \"%s\" failed due to error: %3$s\n";

const char* EXIT = "exit";

const char* QUIT = "quit";

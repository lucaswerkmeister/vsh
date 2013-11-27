TODO
====

Better builtin management
-------------------------

At the moment, builtins are stored in an array and searched with a linear search;
also, the way they are defined and added are rather ugly. I should:
1. define some getBuiltin(char* name) in builtins.{h,c} to remove the search from vsh.c,
   allowing me to change the search and storage without any changes outside builtins.c
2. add some addBuiltin(char* name, bool takesArguments, void (*command)) that will dynamically
   malloc the struct; this function will declutter initBuiltins

A few more builtins
-------------------

Actually, I feel like only one of the builtins from builtins(1) would make sense:
suspend.

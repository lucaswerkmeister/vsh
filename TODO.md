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

Better interrupt handling
-------------------------

An interrupt (CTRL-C) should cancel the current readline() and re-readline().
According to [this stackoverflow answer][so_siglongjmp], this can be achieved with siglongjmp;
however, according to the siglongjmp(3) manpage (and common sense), this "make[s] programs hard to understand and maintain",
so I’ll hold off on that to avoid making the job of the tutor unnecessarily hard :)

[so_siglongjmp]: http://stackoverflow.com/a/17035073

vsh
===

`vsh` is the Verbatim/Verbose SHell.

It’s the year 2013. Filenames with spaces have been in use for several decades now.
And yet, no popular shell can nicely handle them: They all require you to escape the spaces, usually with something like:

    less Curriculum\ Vitae.txt
    less "Curriculum Vitae.txt"

It gets even more complicated if your filename contains other special characters, like "Curriculum Vitae (final).txt", which
may try to spawn a subshell, or "CURRIC~1.TXT", which will replace the tilde ('~') with your home directory.

Enter `vsh`. Everything you enter is passed on *verbatim*. No stupid escape sequences, no backslash hell. Just this:

    Enter a command: less
    Enter an argument, or nothing to end arguments: Curriculum Vitae (final).txt
    Enter an argument, or nothing to end arguments: 

That’s it!

Builtin commands
----------------

### cd, change directory

Change the current directory to the specified one. Takes 1 argument.

### exit, quit

Exits the shell.

Compilation options
-------------------

### Expert mode

With default settings, `vsh` tells you exactly what it expects each time it asks you for a command or an argument;
this is to help people who are coming from other shells, and who might be tempted to just enter "/usr/bin/less filename.txt".
However, once you’ve gotten familiar with `vsh`, you probably don’t need this reminder anymore, and as it takes away a lot of
screen space, you want to get rid of it. Nothing easier than that – just compile with "-D  EXPERT", or using the makefile:

    make expert

and you’ll get a much more useful command prompt (including your username, hostname, and working directory).

TODO
====

next features
-------------------------

	-have colors
	-resize
    -mode handling
	-scrollable history

important for the lols
---------------------

	-parse the font to enjoy a leak free experience

not fun to do
------------
	-fix yes
	-look for crashes
    -ensure proper memory managment (no leaks)

Roadmap
==============

make it work with vim
---------------------

make it work with gdb tui
--------------------------

make it work with all my neovim plugins
------------------

Notes:
======

terminal needs to create a pseudo terminal which is basically two fds
-a parent
-a child

then it needs to fork a child process and launch a shell in it

//this can either be achieved with openpty and execve or forkpty

the terminal emulator will then get the user input via x11 events, pass it to the child fd
the child process (most certainly a shell) will use it and output something
the emulator will draw according to that output

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


backspace might be shitty and cause segfaults at the moment

TODO
====

roadmap to usable terminal
	-have zsh (colors)
	-scrollable history
	-resize

important for the lols
	-parse the font to enjoy a leak free experience

make zsh work
make vim work

not fun to do
	- fix yes
	- check points of failure and make sure everything is freed properly

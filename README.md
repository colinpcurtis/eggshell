# eggshell: the sorta-POSIX compliant shell

This project is mainly just for me to explore systems programming in C in a bit more depth.

## Building
To build the project,
```bash
git clone https://github.com/colinpcurtis/eggshell.git && cd eggshell
```
then finally run the `make` command to build eggshell.

To run the program, run `./eggshell` and when you're done either `CTRL-C` or `exit`.

## Features
- we can run almost any normal shell command (ls, cd)
- we display the username and current directory on the prompt
- multiple execution (separate multiple commands to be run by ';')
- when the previous command has a non-zero exit status the prompt is red

## In Progress
Some things that will be added to eggshell in the near future are
- redirection of stdin and stdout
- pipes
- subshells
- history
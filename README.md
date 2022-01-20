# basic-shell: the non-POSIX compliant, no-error handling shell

This project is mainly just for me to explore systems programming in C in a bit more depth.

## Building
To build the project,
```bash
git clone https://github.com/colinpcurtis/basic-shell.git
```
then 
```bash
cd basic-shell
```
and finally run the `make` command to build the program.

To run the shell, run `./shell` and when you're done either `CTRL-C` or `exit`.

## Features
- we can run almost any normal shell command except for fancy stuff like subshells
- when the previous command has a non-zero exit status the prompt is red
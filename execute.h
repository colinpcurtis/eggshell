#pragma once

#include <unistd.h>

void handle_cd(char** argv, pid_t* prev_status);

void handle_help(char** argv, pid_t* prev_status);

void handle_exit(char** argv, pid_t* prev_status);

void handle_clear(char** argv, pid_t* prev_status);

int handle_builtins(char** argv, pid_t* prev_status);

void execute(char** argv, pid_t* prev_status);

#pragma once
#include <unistd.h>

#define MAX_LENGTH 128
#define MAX_ARGS 16
#define RED "\033[1;31m"
#define RESET "\033[0m"

void parse(char* line, char** argv);

void execute(char** argv, pid_t* prev_status);

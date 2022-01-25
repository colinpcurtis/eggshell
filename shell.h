#pragma once
#include <unistd.h>

#define MAX_LENGTH 128
#define MAX_ARGS 16
#define RED "\033[1;31m"
#define RESET "\033[0m"

/* 
    splits input on special characters like ';'
    to allow for multiple execution
*/
void split_input(char* line, char** split_line);

void parse(char* line, char** argv);

void execute(char** argv, pid_t* prev_status);

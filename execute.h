#pragma once

#include <unistd.h>

void handle_cd(char** const argv, pid_t* prev_status);

void execute(char** const argv, pid_t* prev_status);

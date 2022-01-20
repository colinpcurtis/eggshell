#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "shell.h"

void parse(char* line, char** argv) {
    char* token = strtok(line, " ");
    int argc = 0;
    while (token != NULL) {
        token[strcspn(token, "\n")] = 0; // remove any newline characters from string (usually at last position)
        argv[argc] = token;
        argc++;
        token = strtok(NULL, " ");
    }
    argv[argc] = NULL; // final item must be null terminated
}

void execute(char** argv, pid_t* prev_status) {
    if (strcmp(*argv, "cd") == 0) {
        // TODO: cd with no args should just take us to the home directory
        pid_t status = chdir(argv[1]);
        *prev_status = status;
    }
    else if (strcmp(*argv, "echo") == 0 && argv[1] != NULL && strcmp(argv[1], "$?") == 0) {
        // handle return codes for previous command
        printf("%d\n", *prev_status);
        return;
    }
    pid_t pid = fork();
    if (pid == 0) {
        execvp(*argv, argv);
    }
    waitpid(pid, prev_status, 0);
}
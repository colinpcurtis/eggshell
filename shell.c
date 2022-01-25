#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "shell.h"

void split_input(char* line, char** split_line) {
    char* token = strtok(line, ";");
    int splits = 0;
    while (token != NULL) {
        token[strcspn(token, "\n")] = 0;
        split_line[splits] = token;
        token = strtok(NULL, ";");
        splits++;
    }
    split_line[splits] = NULL;
}

void parse(char* line, char** argv) {
    // split input by space characters and append parameters to argv
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
        return;
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

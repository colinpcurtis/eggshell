#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "execute.h"

void handle_cd(char** const argv, pid_t* prev_status) {
    // TODO: cd with no args should just take us to the home directory
    pid_t status = chdir(argv[1]);
    *prev_status = status;
    return;
}

void execute(char** const argv, pid_t* prev_status) {
    if (strcmp(*argv, "cd") == 0) {
        handle_cd(argv, prev_status);
        return;
    }
    else if (strcmp(*argv, "echo") == 0 && argv[1] != NULL && strcmp(argv[1], "$?") == 0) {
        // handle return codes for previous command
        // TODO: need better parser for finding strings that contain $?
        printf("%d\n", *prev_status);
        return;
    }
    pid_t pid = fork();
    if (pid == 0) {
        execvp(*argv, argv);
    }
    waitpid(pid, prev_status, 0);
}

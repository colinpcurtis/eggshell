#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "execute.h"

void (*builtin_functions[]) (char** argv, pid_t* prev_status) = { handle_cd, handle_help, handle_exit, handle_clear };
char* builtin_strings[] = { "cd", "help", "exit", "clear", NULL };

void handle_cd(char** argv, pid_t* prev_status) {
    if (argv[1] == NULL || strcmp(argv[1], "~") == 0) {
        // user just types "cd" or "cd ~"
        pid_t status = chdir(getenv("HOME"));
        *prev_status = status;
        return;
    }
    pid_t status = chdir(argv[1]);
    *prev_status = status;
    return;
}

void handle_help(__attribute__((unused)) char** argv, pid_t* prev_status) {
    printf("eggshell is a simple Unix Shell\nWritten by Colin Curtis, 2022\n");
    *prev_status = 0;
}

void handle_exit(__attribute__((unused)) char** argv, __attribute__((unused)) pid_t* prev_status) {
    exit(0);
}

void handle_clear(__attribute__((unused)) char** argv, pid_t* prev_status) {
    system("clear");
    *prev_status = 0;
}

int handle_builtins(char** argv, pid_t* prev_status) {
    for (int i = 0; builtin_strings[i] != NULL; i++) {
        if (strcmp(builtin_strings[i], *argv) == 0) {
            // run correct handler for given command
            void (*handler) (char** argv, pid_t* prev_status) = (*builtin_functions[i]);
            handler(argv, prev_status);
            return 1;
        }
    }
    return 0;
}

void execute(char** argv, pid_t* prev_status) {
    if (handle_builtins(argv, prev_status) == 1) {
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

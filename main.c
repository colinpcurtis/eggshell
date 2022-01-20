#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "shell.h"

int main() {
    char line[MAX_LENGTH];
    char* argv[MAX_ARGS];
    pid_t prev_status = 0;

    system("clear");
    while (1) {
        if (prev_status != 0) {
            printf("%s", RED);
        }
        printf("basic-shell> ");
        printf("%s", RESET);
        fflush(stdout);
        fgets(line, MAX_LENGTH, stdin);

        if (strcmp(line, "exit\n") == 0) {
            exit(1);
        }

        parse(line, argv);
        execute(argv, &prev_status);
    }
}

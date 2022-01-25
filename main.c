#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "shell.h"

int main() {
    char line[MAX_LENGTH];
    char cwd[MAX_LENGTH];
    char username[MAX_LENGTH];

    char* split_line[MAX_ARGS];
    char* argv[MAX_ARGS];

    pid_t prev_status = 0;

    system("clear");
    while (1) {
        char* current_directory = getcwd(cwd, MAX_LENGTH);
        getlogin_r(username, MAX_LENGTH);

        if (prev_status != 0) {
            printf("%s", RED);
        }
        printf("%s:%s$ ", username, current_directory);
        printf("%s", RESET);
        fflush(stdout);

        fgets(line, MAX_LENGTH, stdin);

        if (strcmp(line, "exit\n") == 0) {
            exit(1);
        }

        split_input(line, split_line);
        for (int i = 0; split_line[i] != NULL; i++) {
            parse(split_line[i], argv);
            execute(argv, &prev_status);
            if (prev_status != 0) {
                break;
            }
        }
    }
}

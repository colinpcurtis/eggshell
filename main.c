#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "globals.h"
#include "parser.h"
#include "execute.h"

void print_prompt() {
    char cwd[MAX_STRING_LENGTH];
    char username[MAX_STRING_LENGTH];

    char* current_directory = getcwd(cwd, MAX_STRING_LENGTH);
    getlogin_r(username, MAX_STRING_LENGTH);

    
    printf("%s:%s$ ", username, current_directory);
    printf("%s", RESET);
    fflush(stdout);
}

int main() {
    char line[MAX_STRING_LENGTH];
    char* split_line[MAX_ARGS];
    char* argv[MAX_ARGS];

    pid_t prev_status = 0;

    system("clear");
    while (1) {
        if (prev_status != 0) {
            printf("%s", RED);
        }
        print_prompt();

        fgets(line, MAX_STRING_LENGTH, stdin);

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

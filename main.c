#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_LENGTH 128
#define MAX_ARGS 16
#define RED "\033[1;31m"
#define RESET "\033[0m"


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

int main() {
    char line[MAX_LENGTH];
    char* argv[MAX_ARGS];
    pid_t prev_status;

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

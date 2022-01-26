#include <stdlib.h>
#include <string.h>

#include "parser.h"


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
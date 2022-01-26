#pragma once

/* 
    splits input on special characters like ';'
    to allow for multiple execution
*/
void split_input(char* line, char** split_line);

/* 
    parses string in split input by space
    character and appends to argv
*/
void parse(char* line, char** argv);

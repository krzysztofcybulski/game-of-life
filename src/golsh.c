#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define BUFFSIZE 1024
#define DELIM " \t\n\r\a"

#include "game/golsh.h"

char *golsh_read_line() {
    int buffsize = BUFFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof *(buffer) * BUFFSIZE);
    int c;

    if (buffer == NULL) {
        printf("Pamiec nie zosta³a zaalokowana!");
        exit(EXIT_FAILURE);
    }

    while (1) {
        c = getchar();

        if(c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;

        if(position >= buffsize) {
            buffsize *= 2;
            char *new_buffer = realloc(buffer, buffsize);
            if(new_buffer == NULL) {
                printf("Problemy z alolakacja pamieci!");
                exit(EXIT_FAILURE);
            }
            buffer = new_buffer;
        }
    }
}

char **golsh_split_line(char *line) {
    int buffsize = BUFFSIZE;
    char **tokens = malloc(sizeof(char) * buffsize);
    char *token= NULL;
    int position = 0;

    if(tokens == NULL) {
        printf("pamiec!");
        exit(EXIT_FAILURE);
    }
    token = strtok(line, DELIM);

    while (token != NULL) {
        tokens[position] = token;
        position++;
        if (position >= BUFFSIZE) {
            buffsize *= 2;
            char **new_tokens = realloc(tokens, buffsize);
            if (new_tokens == NULL) {
                printf("pamiec");
                exit(EXIT_FAILURE);
            }
            tokens = new_tokens;
        }
        token = strtok(NULL, DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}
void help() {
    printf("Info and instuction about available function\n");
    printf("%-20s %s\n","SET_RULES", "PRINT RULES");
}

int run(char **command) {
	//to lower
	char *c;
	for(c = command[0]; *c != '\0'; c++) {
		*c = tolower(*c);
	}

    if (strcmp(command[0], "help")==0 && command[1] == NULL) {
        help();
    //} else if(command[0], "set_rules") {
  //      set_rules();
    } else if (strcmp(command[0], "exit")==0) {
    	exit(EXIT_SUCCESS);
    } else
        return 1;

    return 1;
}
void golsh_loop() {
    char *line;
    char **args;
    int status;

    do {
        printf("> ");
        line = golsh_read_line();
        args = golsh_split_line(line);
        status = run(args);

    } while (status);
}



/*
int main (int argc, char **argv) {

    golsh_loop();


    return 0;
}
*/
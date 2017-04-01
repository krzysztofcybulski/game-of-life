#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "game/map.h"
#include "game/rules.h"
#include "game/game.h"

#define BUFFSIZE 1024
#define DELIM " \t\n\r\a"

#include "game/golsh.h"

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
    printf("%-20s %s\n","SET_RULE", "set_rule <nazwa>");
    printf("%-20s %s\n","EXIT", "konczy program");
    printf("%-20s %s\n","SHOW_RULES", "pokazuje dostepne zasady");
    printf("%-20s %s\n","SET_SIZE", "set_size <rozmiar>");
    printf("%-20s %s\n","PLACE", "place <x> <y> <nazwa>");
    printf("%-20s %s\n","SET", "set <x> <y> [stan]");
    printf("%-20s %s\n","GO", "go <n>");
    printf("%-20s %s\n","NEXT OR N", "przychodzi jedna generacje dalej");
    printf("%-20s %s\n","BACK OR B", "cofa sie o jedna generacje");
    printf("%-20s %s\n","PLAY", "play <n> [delay] [name]");
    printf("%-20s %s\n","SHOW", "wyświetla okno z wizualizacją planszy");
    printf("%-20s %s\n","SAVE", "zapisuje plik .png o nazwie [name]");

}
void show_rules() {
    printf("1. Sasiedztwo Moore'a  \n");

}
int set_rules(char **command) {
	;
}
int set_size(char **command) {
	;
}
int set(char **command) {
	;
}
int go(char **command) {
	;
}
int next() {
	//int increment(map_t, int, int);
		;
}
int back() {
	//int inverse(map_t, int, int);	
	;
}
int play(char **command) {
	;
}

int show() {
	;
}
int save(char **command) {
	;
}	


int ruun(char **command) {
	//to lower
	char *c;
	for(c = command[0]; *c != '\0'; c++) {
		*c = tolower(*c);
	}

    if (strcmp(command[0], "help")==0 && command[1] == NULL) {
        help();
    } else if (strcmp(command[0], "exit")==0) {
    	exit(EXIT_SUCCESS);
    } else if (strcmp(command[0], "show_rules") == 0) {
    	show_rules();
    } else if (strcmp(command[0], "set_rules") == 0) {
    	set_rules(command);
    } else if (strcmp(command[0], "set_size") == 0) {
    	set_size(command);
//    } else if (strcmp(command[0], "place") == 0) {
//    	place();
    } else if (strcmp(command[0], "set") == 0) {
    	set(command);
    } else if (strcmp(command[0], "go") == 0) {
    	go(command);
    } else if (strcmp(command[0], "next") == 0 || strcmp(command[0], "n")) {
    	next();
    } else if ((strcmp(command[0], "back") == 0) || (strcmp(command[0], "b")) == 0) {
    	back();
    } else if (strcmp(command[0], "play") == 0) {
    	play(command);
    } else if (strcmp(command[0], "show") == 0) {
    	show();
    } else if (strcmp(command[0], "save") == 0) {
    	save(command);

    } else
        return 1;

    return 1;
}
void golsh_loop() {
    char *line;
    char **args;
    int status;
    char buffer[BUFFSIZE];

    do {
        printf("> ");
        line = fgets(buffer, BUFFSIZE, stdin);
        args = golsh_split_line(line);
        status = ruun(args);

    } while (status);
}



/*
int main (int argc, char **argv) {

    golsh_loop();


    return 0;
}
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "game/map.h"
#include "game/rules.h"
#include "game/game.h"
#include "game/png_generator.h"
#include "game/game_cmds.h"

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
void help_c(char **command, game_t game) {
    printf("Info and instuction about available function\n");
    printf("%-20s %s\n","SET_RULE", "set_rule <nazwa>");
    printf("%-20s %s\n","EXIT", "konczy program");
    printf("%-20s %s\n","SHOW_RULES", "pokazuje dostepne zasady");
    printf("%-20s %s\n","SET_SIZE", "set_size <rozmiar>");
    printf("%-20s %s\n","PLACE", "place <x> <y> ");
    printf("%-20s %s\n","NEXT OR N", "przychodzi jedna generacje dalej");
    printf("%-20s %s\n","PLAY", "play <n> [delay] [name]");
    printf("%-20s %s\n","SNAP", " snap <name> zapisuje plik .png o nazwie name");
    printf("%-20s %s\n","CLEAN", "czysci plansze");
    printf("%-20s %s\n","RANDOM", "random <x>, Losowe zapelnienie planszy w x%");

}
void show_rules_c(char **command, game_t game) {
    ;
}
void set_rules_c(char **command, game_t game) {
	;
}
void place_c(char **command, game_t game) {
    int tmp = atoi(command[1]);
    int tmp2 = atoi(command[2]);

    int actives[] = {(tmp * game->map->width) + tmp2};
    place(game, (int*)actives, 1);
    printf("Placed cell in %d %d\n", tmp, tmp2);
}
void set_size_c(char **command, game_t game) {
    int tmp = atoi(command[1]);
    int tmp2 = atoi(command[2]);
    clean(game, tmp, tmp);
    printf("Set size to %dx%d\n", tmp, tmp2);   	
}
void next_c(char **command, game_t game) {
    move(game, 1, 0, NULL);
		
}
void play_c(char **command, game_t game) {
    int tmp = atoi(command[1]);
    int tmp2 = atoi(command[2]);
    move(game, tmp, tmp2, command[3]);
}
void random_c(char **command, game_t game) {
    int tmp = atoi(command[1]);
    random_map(game, tmp);
    move(game, 1, 0, NULL);
}
void snap_c(char **command, game_t game) {
    snap(game, command[1]);

}	
void clean_c(char **command, game_t game) {
    clean(game, game->map->height, game->map->width);
    move(game, 1, 0, NULL);  
}   

int ruun(char **command, game_t game) {
	//to lower
	char *c;
	for(c = command[0]; *c != '\0'; c++) {
		*c = tolower(*c);
	}

    if (strcmp(command[0], "help")==0 && command[1] == NULL) {
        help_c(command, game);
    } else if (strcmp(command[0], "exit")==0) {
    	exit(EXIT_SUCCESS);
    } else if (strcmp(command[0], "show_rules") == 0) {
    	show_rules_c(command, game);
    } else if (strcmp(command[0], "set_rules") == 0) {
    	set_rules_c(command, game);
    } else if (strcmp(command[0], "clean") == 0) {
        clean_c(command, game);
    } else if (strcmp(command[0], "set_size") == 0) {
    	set_size_c(command, game);
    } else if (strcmp(command[0], "place") == 0) {
    	place_c(command, game);
    } else if (strcmp(command[0], "next") == 0 || strcmp(command[0], "n")==0) {
    	next_c(command, game);
    } else if (strcmp(command[0], "play") == 0) {
    	play_c(command, game);
    } else if (strcmp(command[0], "snap") == 0) {
    	snap_c(command, game);
    } else if (strcmp(command[0], "random") == 0) {
        random_c(command, game);
    } else {
        printf("Nie ma takiej komendy, wpisz help aby uzyskac pomoc\n");
        return 1;
    }   

    return 1;
}
void golsh_loop(game_t game) {
    char *line;
    char **args;
    int status;
    char buffer[BUFFSIZE];

    do {
        printf("> ");
        line = fgets(buffer, BUFFSIZE, stdin);
        args = golsh_split_line(line);
        status = ruun(args, game);

    } while (status);
}

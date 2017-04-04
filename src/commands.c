#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "parser/commands.h"

#include "game/map.h"
#include "game/rules.h"
#include "game/game.h"
#include "game/game_cmds.h"

#define BUFFSIZE 1024
#define DELIM " \t\n\r\a"

char **golsh_split_line(char *line) {
    int buffsize = BUFFSIZE;
    char **tokens = malloc(sizeof(char) * buffsize);
    char *token= NULL;
    int position = 0;

    if(tokens == NULL) {
        printf("No memory!\n");
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


int run_cmd(char **command, game_t game, parser_t parser) {
	if(command[0] == NULL)
		return 1;
	int i;
	for(i = 0; i < parser->commands_amount; i++)
		if(strcmp(parser->commands[i]->name, command[0]) == 0)
			return parser->commands[i]->cmd(command, game);

	if(strcmp(command[0], "help"))
		printf("No such command!\n");
	print_help(parser);
	return 1;
}

void golsh_loop(game_t game, parser_t parser) {
    char *line;
    char **args;
    char buffer[BUFFSIZE];
    do {
        printf("Game of Life> ");
        line = fgets(buffer, BUFFSIZE, stdin);
        args = golsh_split_line(line);
    } while (run_cmd(args, game, parser));
}
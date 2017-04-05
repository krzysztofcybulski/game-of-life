#ifndef GOL_C_CMD_H
#define GOL_C_CMD_H

#include "../game/game.h"

#define MAX_NAME_LENGTH 256

typedef struct Command {
	char *name;
	char *help;
	int (*cmd)(char **, game_t);
} *cmd_t;

typedef struct Parser {
	cmd_t *commands;
	int commands_amount;
} *parser_t;

parser_t alloc_parser(int);
int register_cmd(parser_t parser, char *name, void *help, int (*cmd)(char **, game_t));
void print_help(parser_t);
int print_dir(char *name, char *type);

#endif
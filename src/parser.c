#include <stdlib.h>

#include "parser/parser.h"

parser_t alloc_parser(int n) {
	parser_t parser = (parser_t) malloc(sizeof(struct Parser));
	parser->commands = malloc(n * sizeof(cmd_t));
	parser->commands_amount = 0;
	return parser;
}

int register_cmd(parser_t parser, char *name, void *help, int (*cmd)(char **, game_t)) {
	cmd_t command = (cmd_t) malloc(sizeof(struct Command));
	command->name = name;
	command->help = help;
	command->cmd = cmd;
	parser->commands[parser->commands_amount++] = command;
	return 1;
}

void print_help(parser_t parser) {
	int i;
	for(i = 0; i < parser->commands_amount; i++)
		printf("%-20s %s\n", parser->commands[i]->name, parser->commands[i]->help);
}
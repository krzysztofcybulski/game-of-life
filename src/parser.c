#include <stdlib.h>
#include <dirent.h>

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

int print_dir(char *name, char *type) {
	struct dirent *file;
	DIR * path;
	int i = 1;

	if((path = opendir((name))) != NULL) {
		while((file = readdir(path)) != NULL) {
			if (file->d_name[0] != '.'){
				printf("%s %d: %s\n", type, i, file->d_name);
				i++;
			}
		}
		closedir(path);
	} else {
		printf("Can't open structures dir");
		return 0;
	}
	
	return 1;
}
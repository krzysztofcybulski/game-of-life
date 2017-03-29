#ifndef GOL_C_PARSER_H
#define GOL_C_PARSER_H

typedef struct Parser {
	cmd_t *commands;
} *parser_t;

int register_cmd(parser_t, cmd_t);
cmd_t load_cmd(parser_t, char* name);

#endif
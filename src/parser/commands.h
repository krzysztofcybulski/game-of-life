#ifndef GOL_C_GAME_COMMANDS_H
#define GOL_C_GAME_COMMANDS_H

#include "parser.h"
#include "../game/game.h"

char **golsh_split_line(char *line);
int run_cmd(char **command, game_t game, parser_t parser);
void golsh_loop(game_t game, parser_t parser);

#endif
#ifndef GOL_C_CMD_PROXY_H
#define GOL_C_CMD_PROXY_H

#include "parser.h"
#include "../game/game.h"

int register_all_cmds(parser_t parser);
int show_rules_c(char **command, game_t game);
int set_rules_c	(char **command, game_t game);
int place_c		(char **command, game_t game);
int set_size_c	(char **command, game_t game);
int next_c		(char **command, game_t game);
int play_c		(char **command, game_t game);
int random_c	(char **command, game_t game);
int snap_c		(char **command, game_t game);
int clean_c		(char **command, game_t game);
int exit_c		(char **command, game_t game);

#endif
#ifndef GOL_C_GAME_CMDS_H
#define GOL_C_GAME_CMDS_H

#include "game.h"
#include "map.h"

void print_map(map_t map);
void print_actives(game_t game);
int move(game_t game, int n, int delay_time, char* filename);
int random_map(game_t game, int density);
int clean(game_t game, int height, int width);
int snap(game_t game, char *name);
int gif(char *name, int delay);

#endif
#ifndef GOL_C_GAME_CMDS_H
#define GOL_C_GAME_CMDS_H

void print_map(map_t map);
void print_actives(game_t game);
void move(game_t game, int n, int delay_time, char* filename);
void random_map(game_t game, int density);
void clean(game_t game, int height, int width);
void snap(game_t game, char *name);

#endif
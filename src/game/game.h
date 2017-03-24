#ifndef GOL_C_GAME_H
#define GOL_C_GAME_H

#include "map.h"
#include "rules.h"

typedef struct Game {
	map_t map;
	rules_t rules;
    int age;
} *game_t;

game_t start(rules_t, map_t);
int step(game_t);
int end(game_t);

#endif
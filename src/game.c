#include "game/game.h"

#include <stdlib.h>

int is_active(game_t, int);

game_t start(rules_t rules, map_t map) {
	game_t game = (game_t) malloc(sizeof(struct Game));
	
	game->map = map;
	game->rules = rules;
	game->age = 0;
	game->actives = NULL;
	game->actives_amount = 0;
	
	return game;
}

int step(game_t game) {	
	return NULL;
}

int is_active(game_t game, int state) {
	rules_t rules = game->rules;
	int i;
	
	if(state > 0) {
		for(i = 0; i < rules->live_n; i++)
			if(state == rules->live[i])
				return 1;
		return 0;
	}
	else {
		for(i = 0; i < rules->born_n; i++)
			if(state == rules->born[i])
				return 0;
		return 1;
	}
}

int end(game_t game) {
	return 0;
}
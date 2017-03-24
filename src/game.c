#include "game/game.h"

#include <stdlib.h>

int is_active(game_t, int);

game_t start(rules_t rules, map_t map) {
	game_t game = (game_t) malloc(sizeof(game_t));
	
	game->map = map;
	game->rules = rules;
	game->age = 0;
	game->active = malloc(sizeof(int));
	game->active_amount = 0;
	
	return game;
}

int step(game_t game) {	
	int *active = malloc(sizeof(int) * 8 * game->active_amount);
	int active_amount = 0;
	int i;

	for(i = 0; i < game->active_amount; i++) {
		int ax = game->active[i] % game->map->width + 1;
		int ay = game->active[i] / game->map->width;
		inverse(game->map, ax, ay);			
	}
	
	for(i = 0; i < game->active_amount; i++) {
		int ax = game->active[i] % game->map->width;
		int ay = game->active[i] / game->map->width;
		
		int j;
		int (*neighbors)[2] = game->rules->neighbors;
		
		for(j = 0; j < game->rules->neighbors_amount; j++)
			if(is_active(game, increment(game->map, ax + neighbors[j][0], ay + neighbors[j][1])))
				active[active_amount++] = (ay + neighbors[j][1] * game->map->width) + ax + neighbors[j][0];
	}
	
	game->active = active;
	game->active = realloc(game->active, active_amount * sizeof(int));
	game->active_amount = active_amount;
	game->age++;
	
	return active_amount; //TODO!
}

int is_active(game_t game, int state) {
	rules_t rules = game->rules;
	int i;
	
	if(state > 0) 
		for(i = 0; i < sizeof(rules->live) / sizeof(int); i++)
			if(state == rules->live[i])
				return 1;
	else
		for(i = 0; i < sizeof(rules->born) / sizeof(int); i++)
			if(state == rules->born[i])
				return 0;
	
	return 1;
}

int end(game_t game) {
	return 0;
}
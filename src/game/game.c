#include "game.h"

#include <stdlib.h>

int load_actives(game_t);
int is_active(game_t, int, int);

game_t start(rules_t rules, map_t map) {
	game_t game = (game_t) malloc(sizeof(game_t));
	
	game->map = map;
	game->rules = rules;
	game->age = 0;
	game->active_amount = load_actives(game);
	
	return game;
}

int step(game_t game) {
	
	int *active = malloc(sizeof(int) * 8 * game->active_amount);
	int active_amount = 0;
	
	int i;
	
	for(int i = 0; i < game->active_amount; i++) {
		int ax = game->active[i] % game->map->width;
		int ay = game->active[i] / game->map->width;
		inverse(map, ax, ay);			
	}
	
	for(int i = 0; i < game->active_amount; i++) {
		int ax = game->active[i] % game->map->width;
		int ay = game->active[i] / game->map->width;
		
		int j;
		int **neighbors = game->rules->neighbors;
		
		for(j = 0; j < game->rules->neighbors_amount; j++)
			if(is_active(increment(map, ax + neighbors[j][0], ay + neighbors[j][1])))
				active[active_amount++] = (ay + neighbors[j][1] * game->map->width) + ax + neighbors[j][0]);
	}
	
	game->age++;
	
	return 0; //TODO!
}

int load_actives(game_t game) {
	return 0;
}

int is_active(game_t game, int x, int y) {
	return 0;	
}

int end(game_t game) {
	return 0;
}
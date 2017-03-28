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

int is_active(game_t game, int state) {
	rules_t rules = game->rules;
	int i;
	
	
	if(state >= SPLITTER) {
		for(i = 0; i < rules->live_n; i++)
			if(state == rules->live[i])
				return 0;
		return 1;
	}
	else {
		for(i = 0; i < rules->born_n; i++)
			if(state == rules->born[i])
				return 1;
		return 0;
	}
}

int invert_actives(map_t map, int* actives, int n) {
	int i;
	for(i = 0; i < n; i++)
		invert(map, actives[i]);
	return 0;
}

int step(game_t game) {

	int i, j;
	int *new_actives = (int*) malloc(game->actives_amount * 8 * sizeof(int));
	int new_actives_amount = 0;
	invert_actives(game->map, game->actives, game->actives_amount);
	
	printf("%d %d\n", game->actives_amount, game->rules->neighbours_amount);
	
	for(i = 0; i < game->actives_amount; i++)
		for(j = 0; j < game->rules->neighbours_amount; j++) {
			printf("%d\n", game->actives[i]);
			increment(game->map, game->actives[i] + game->rules->neighbours[j][0] + (game->map->width * game->rules->neighbours[j][1]), game->actives[i]);
		}
	
	for(i = 0; i < game->actives_amount; i++)
		for(j = 0; j < game->rules->neighbours_amount; j++) {
			int position = game->actives[i] + game->rules->neighbours[j][0] + (game->map->width * game->rules->neighbours[j][1]);
			int x = position % game->map->width;
			int y = position / game->map->width;
			printf("%d %d %d %d\n", x, y, x >= 0 && x < game->map->width && y >= 0 && y < game->map->height, is_active(game, game->map->cells[position]));
			if(x >= 0 && x < game->map->width && y >= 0 && y < game->map->height && is_active(game, game->map->cells[position])) {
				int k = 0;
				while(new_actives[k] != position && k < new_actives_amount){k++;}
				if(k == new_actives_amount)
					new_actives[new_actives_amount++] = position;
			}
		}
	
	free(game->actives);
	new_actives = realloc(new_actives, new_actives_amount * sizeof(int));
	game->actives = new_actives;
	game->actives_amount = new_actives_amount;
	game->age++;
	
	return 0;
}

int place(game_t game, int *actives, int n) {
	int i;
	int current_n = game->actives_amount;
	int size = current_n + n;
	
	game->actives = (int*) realloc(game->actives, size * sizeof(int));
	
	for(i = current_n; i < size; i++)
		game->actives[i] = actives[i - current_n];
	
	game->actives_amount = size;
	
	return 0;
}
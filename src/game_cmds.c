#include <stdio.h>
#include <stdlib.h>

#include "game/game.h"
#include "game/map.h"
#include "utils/delay.h"

void print_map(map_t map) {
	int i, j;
	for(i = 0; i < map->height; i++) {
		for(j = 0; j < map->width; j++)
			printf("%d ", map->cells[i * map->width + j] > SPLITTER ? map->cells[i * map->width + j] % 10 : 0);
		printf("\n");
	}
}

void print_actives(game_t game) {
	printf("n = %d (%d)\n", game->actives_amount, game->actives_amount * (game->rules->neighbours_amount * 2 + 1));
}

void move(game_t game, int n, int delay_time) {
	step(game);
	system("clear");
	print_actives(game);
	print_map(game->map);
	
	delay(delay_time);
	
	if(n > 0)
		move(game, --n, delay_time);
}
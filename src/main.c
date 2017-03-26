#include <stdio.h>
#include <stdlib.h>

#include "utils/colors.h"

#include "game/game.h"
#include "game/rules.h"
#include "game/map.h"

void print_map(map_t map) {
	int i, j;
	for(i = 0; i < map->height; i++) {
		for(j = 0; j < map->width; j++)
			printf("%d ", map->cells[i * map->width + j] > SPLITTER ? map->cells[i * map->width + j] % 10 : 0);
		printf("\n");
	}
}

void print_actives(game_t game) {
	int i;
	printf("Active cells [%d]: {", game->actives_amount);
	for(i = 0; i < game->actives_amount; i++)
		printf("%d, ", game->actives[i]);
	printf("}\n");
}

void move(game_t game, int n) {
	step(game);
	print_actives(game);
	print_map(game->map);
	
	if(n > 0)
		move(game, --n);
}

int main(int argc, char **argv) {
	
	/*TEST RULES*/
	rules_t r = (rules_t) malloc(sizeof(struct Rules));
	r->name = "test";
	int live[2] = {12, 13};
	r->live = (int*)live;
	r->live_n = 2;
	int born[1] = {3};
	r->born = (int*)born;
	r->born_n = 1;
	int neighbours[8][2] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};
	int (*ne)[2] = neighbours;
	r->neighbours_amount = 8;
	r->neighbours = ne;
	
	map_t map = alloc_map(8, 8);
	game_t game = start(r, map);
	
	int actives[3] = {12, 20, 28};
	place(game, (int*)actives, 3);
	
	move(game, 10);
	
	return EXIT_SUCCESS;
}
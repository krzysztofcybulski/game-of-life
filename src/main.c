#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils/colors.h"

#include "game/game.h"
#include "game/rules.h"
#include "game/map.h"

#include "test/test.h"

void print_map(map_t map) {
	int i, j;
	for(i = 0; i < map->height; i++) {
		for(j = 0; j < map->width; j++)
			printf("%d ", map->cells[i * map->width + j] > SPLITTER ? map->cells[i * map->width + j] % 10 : 0);
		printf("\n");
	}
}

void print_actives(game_t game) {
	printf("n = %d\n", game->actives_amount);
}

void move(game_t game, int n) {
	step(game);
	print_actives(game);
	print_map(game->map);
	
	if(n > 0)
		move(game, --n);
}

int main(int argc, char **argv) {
	
	if(argc > 1 && strcmp(argv[1], "test") == 0) {
		utests_t utests = alloc_utests();
		return print_results(utests);
	}
	
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
	
	map_t map = alloc_map(13, 13);
	game_t game = start(r, map);
	
	int actives[] = {1, 15, 26, 27, 28};
	place(game, (int*)actives, 5);
	
	move(game, 50);
	free(game);
	
	return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>

#include "utils/colors.h"

#include "game/game.h"
#include "game/rules.h"
#include "game/map.h"

int main(int argc, char **argv) {
	
	//TEST RULES
	rules_t r = (rules_t) malloc(sizeof(rules_t));
	r->name = "test";
	int live[2] = {4, 5};
	r->live = (int*)live;
	int born[1] = {-4};
	r->born = (int*)born;
	int neighbors[8][2] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};
	int (*ne)[2] = neighbors;
	r->neighbors_amount = 8;
	r->neighbors = malloc(sizeof(ne));
	r->neighbors = ne;
	
	map_t map = alloc_map(5, 5);
	
	game_t game = start(r, map);
	game->map->cells[12] = 1;
	game->active = malloc(sizeof(int));
	game->active[0] = 12;
	game->active_amount = 1;
	
	step(game);
	
	return EXIT_SUCCESS;
}
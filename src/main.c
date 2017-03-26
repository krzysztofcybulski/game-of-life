#include <stdio.h>
#include <stdlib.h>

#include "utils/colors.h"

#include "game/game.h"
#include "game/rules.h"
#include "game/map.h"

int main(int argc, char **argv) {
	
	/*TEST RULES*/
	rules_t r = (rules_t) malloc(sizeof(struct Rules));
	r->name = "test";
	int live[2] = {3, 4};
	r->live = (int*)live;
	r->live_n = 2;
	int born[1] = {-3};
	r->born = (int*)born;
	r->born_n = 1;
	int neighbors[8][2] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};
	int (*ne)[2] = neighbors;
	r->neighbors_amount = 8;
	r->neighbors = ne;
	
	map_t map = alloc_map(8, 8);
	game_t game = start(r, map);
	
	return EXIT_SUCCESS;
}
#include <stdint.h>

#include "test/test_all.h"
#include "test/test.h"

#include "game/map.h"
#include "game/rules.h"
#include "game/game.h"
#include "game/game_cmds.h"

/* Some simple tests to check all modules */
int test_all() {
	utests_t t = alloc_utests();

	/* Map */
	map_t map = load_map("sample_map");
	test(t, "Cell value", (void*)(intptr_t)map->cells[5], (void*)(intptr_t)13);
	invert(map, 5);
	test(t, "Cell inverted", (void*)(intptr_t)map->cells[5], (void*)(intptr_t)3);
	increment(map, 5, 3);
	test(t, "Cell incremented", (void*)(intptr_t)map->cells[5], (void*)(intptr_t)2);
	
	/* Rules */
	rules_t rules = load_rules("conway_moor");
	test(t, "Rules neighbours amount", (void*)(intptr_t)rules->neighbours_amount, (void*)(intptr_t)8);
	
	/* Game */
	game_t game = start(rules, load_map("spaceship"));
	test(t, "Game cell", (void*)(intptr_t)game->map->cells[0], (void*)(intptr_t)11);
	
	int test_ac[] = {26, 46, 66};
	place(game, (int*) test_ac, 3);
	step(game);
	test(t, "Game place", (void*)(intptr_t)(game->map->cells[46] > SPLITTER), (void*)(intptr_t)1);
	step(game);
	test(t, "Game place", (void*)(intptr_t)(game->map->cells[66] > SPLITTER), (void*)(intptr_t)0);
	
	clean(game, game->map->height, game->map->width);
	test(t, "Game clean", (void*)(intptr_t)(game->map->cells[46] > SPLITTER), (void*)(intptr_t)0);
	
	return print_results(t);
}
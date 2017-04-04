#include <stdio.h>
#include <string.h>

#include "test/test.h"

#include "parser/parser.h"
#include "parser/cmd_proxy.h"
#include "parser/commands.h"

#include "game/map.h"
#include "game/rules.h"
#include "game/game.h"

int main(int argc, char **argv) {
	
	/* Run tests */
	if(argc > 1 && strcmp(argv[1], "test") == 0) {
		utests_t utests = alloc_utests();
		return print_results(utests);
	}
 	
	/* Register all commands */
	parser_t parser = alloc_parser(12);
	register_all_cmds(parser);
	print_help(parser);
	
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
	
	map_t map = alloc_map(20, 20);
	game_t game = start(r, map);
	
    golsh_loop(game, parser);
  
	free(game);
	return EXIT_SUCCESS;
}